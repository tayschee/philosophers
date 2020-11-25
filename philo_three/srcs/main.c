/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbigot <tbigot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 11:00:55 by tbigot            #+#    #+#             */
/*   Updated: 2020/11/25 13:19:41 by tbigot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int				sem(void)
{
	char	*safe;
	int		i;

	i = g_number_of_sophos;
	if ((g_fork = sem_open("fork", O_CREAT | O_EXCL, 0644, i)) == SEM_FAILED)
		return (1);
	if ((g_meal = sem_open("meal", O_CREAT | O_EXCL, 0644, i / 2)) == SEM_FAILED)
		return (2);
	if ((g_write = sem_open("write", O_CREAT | O_EXCL, 0644, 1)) == SEM_FAILED)
		return (3);
	if ((g_kill = sem_open("kill", O_CREAT | O_EXCL, 0644, 0)) == SEM_FAILED)
		return (4);
	if (!(g_safe = malloc(sizeof(sem_t *) * g_number_of_sophos)))
		return (5);
	i = -1;
	while (++i < g_number_of_sophos)
	{
		if (!(safe = name_sem(i)))
			return (5 + i);
		if ((g_safe[i] = sem_open(safe, O_CREAT | O_EXCL, 0644, 1)) == SEM_FAILED)
		{
			free(safe);
			return (6 + i);
		}
		free(safe);
	}
	return (0);
}

void                    ft_usleep(int sleep_time)
{
        t_val   begin;
        t_val   now;

        gettimeofday(&begin, NULL);
		usleep(sleep_time * 500);
        while (1)
        {
            usleep(50);
            now = time_past(begin);
            if (sleep_time - convert_sec_to_msec(now.tv_sec, now.tv_usec) < 0)
            	break ;
        }
}

void			*eat(void *sophos_pointer)
{
	t_sophos	*sophos;
	int			i;

	sophos = (t_sophos *)sophos_pointer;
	i = sophos->number - 1;
	while (g_sophos_die)
	{
		take_fork(i + 1);
		sem_wait(g_safe[i]);
		gettimeofday(&sophos->last_meal, NULL);
		sophos_activity(i + 1, " is eating\n", 1);
		ft_usleep(g_time_to_eat);
		sem_post(g_safe[i]);
		put_fork(sophos);
		if ((g_eat_max != -1 && --g_eat_max == 0))
			break ;
		sophos_activity(i + 1, " is sleeping\n", 1);
		ft_usleep(g_time_to_sleep);
		sophos_activity(i + 1, " is thinking\n", 1);
	}
	sem_wait(g_safe[sophos->number - 1]);
	free_fct(&g_save, NULL, 1);
	close_sem(-1);
	exit(i);
}

int				launch_thread(t_sophos *sophos)
{
	int			i;
	int			status;
	pid_t		pid[g_number_of_sophos];
	int			j;
	pthread_t	tid;

	i = -1;
	j = 0;
	g_save = sophos;
	pthread_create(&tid, NULL, kill_everything, pid);
	pthread_detach(tid);
	gettimeofday(&g_begin, NULL);
	while (++i < g_number_of_sophos)
	{
		if (pid_fct(sophos, &pid[i]) < 0)
			return (1);
		sophos = sophos->next;
	}
	while (j < g_number_of_sophos && waitpid(-1, &status, 0) &&
	WEXITSTATUS(status) != 0)
	{
		j++;
		sem_post(g_safe[WEXITSTATUS(status) - 1]);
	}
	g_sophos_die = 0;
	sem_post(g_kill);
	return (0);
}

int				main(int argc, char **argv)
{
	t_sophos		*sophos;
	int				ret;

	ret = 0;
	g_sophos_die = 1;
	if (check_argv(argc, argv))
	{
		ft_putstr("Les philosophes ne peuvent pas se reunir\n");
		return (1);
	}
	sophos = sophos_sit_down(1, g_number_of_sophos);
	unlink_sem();
	if ((ret = sem()) > 0)
	{
		free_fct(&sophos, 0, ret);
		close_sem(ret);
		unlink_sem();
		return (1);
	}
	ret = launch_thread(sophos);
	unlink_sem();
	close_sem(-1);
	return (free_fct(&sophos, 0, ret));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbigot <tbigot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 11:00:55 by tbigot            #+#    #+#             */
/*   Updated: 2020/11/24 17:34:46 by tbigot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int				sem(void)
{
	char	*safe;
	int		i;

	i = g_number_of_sophos;
	if ((g_fork = sem_open("/fork", O_CREAT | O_EXCL, 0644, i)) == 0)
		return (1);
	if ((g_meal = sem_open("/meal", O_CREAT | O_EXCL, 0644, i / 2)) == 0)
		return (2);
	if ((g_write = sem_open("/write", O_CREAT | O_EXCL, 0644, 1)) == 0)
		return (3);
	if (!(g_safe = malloc(sizeof(sem_t *) * g_number_of_sophos)))
		return (4);
	i = -1;
	while (++i < g_number_of_sophos)
	{
		if (!(safe = name_sem(i)))
			return (4 + i);
		if ((g_safe[i] = sem_open(safe, O_CREAT | O_EXCL, 0644, 1)) == 0)
		{
			free(safe);
			return (5 + i);
		}
		free(safe);
	}
	return (0);
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
		sophos_activity(i + 1, " is eating\n", g_sophos_die, 1);
		usleep(1000 * g_time_to_eat);
		sem_post(g_safe[i]);
		put_fork(sophos);
		if (g_sophos_die && g_eat_max != -1 && --g_eat_max == 0)
			break ;
		sophos_activity(i + 1, " is sleeping\n", g_sophos_die, 1);
		usleep(1000 * g_time_to_sleep);
		sophos_activity(i + 1, " is thinking\n", g_sophos_die, 1);
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

	i = -1;
	j = 0;
	g_save = sophos;
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
	while (--i >= 0 && j < g_number_of_sophos)
		kill(pid[i], SIGKILL);
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
	close_sem(-1);
	unlink_sem();
	return (free_fct(&sophos, 0, ret));
}

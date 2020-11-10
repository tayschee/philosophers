/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbigot <tbigot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 11:00:55 by tbigot            #+#    #+#             */
/*   Updated: 2020/11/10 10:30:30 by tbigot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void		sophos_sleep(t_sophos *sophos)
{
	sophos_activity(sophos->number, " is sleeping\n", g_sophos_die, 1);
	usleep(1000 * g_time_to_sleep);
	sophos_activity(sophos->number, " is thinking\n", g_sophos_die, 1);
}

void			*eat(void *sophos_pointer)
{
	t_sophos	*sophos;

	sophos = (t_sophos *)sophos_pointer;
	while (g_sophos_die)
	{
		take_fork(sophos);
		if (sophos->hand == 2)
		{
			sem_wait(g_safe);
			gettimeofday(&sophos->last_meal, NULL);
			sem_post(g_safe);
			sophos_activity(sophos->number, " is eating\n", g_sophos_die, 1);
			usleep(1000 * g_time_to_eat);
			put_fork(sophos);
			if (sophos->eat_max != -1 && --sophos->eat_max == 0)
				break ;
			sophos_sleep(sophos);
		}
	}
	sem_wait(g_safe);
	exit(0);
}

int				launch_thread(t_sophos *sophos)
{
	int			i;
	int			status;
	pid_t		pid[g_number_of_sophos];
	int			j;

	i = -1;
	j = 0;
	gettimeofday(&g_begin, NULL);
	while (++i < g_number_of_sophos)
	{
		if (pid_fct(sophos, &pid[i]) < 0)
			return (1);
		sophos = sophos->next;
	}
	g_safe = sem_open("/protect", O_RDWR);
	while (j < g_number_of_sophos && waitpid(-1, &status, 0) &&
	WEXITSTATUS(status) == 0)
	{
		j++;
		sem_post(g_safe);
	}
	while (--i >= 0 && j < g_number_of_sophos)
		kill(pid[i], SIGINT);
	sem_post(g_safe);
	return (0);
}

int				main(int argc, char **argv)
{
	t_sophos		*sophos;
	int				ret;

	ret = 0;
	g_sophos_die = 1;
	unlink_sem();
	if (check_argv(argc, argv))
	{
		ft_putstr("Les philosophes ne peuvent pas se reunir\n");
		return (1);
	}
	if ((g_fork = sem_open("/fork", O_CREAT, 0644, g_number_of_sophos)) == 0)
		return (1);
	if ((g_safe = sem_open("/protect", O_CREAT, 0644, 1)) == 0)
		return (1);
	if ((g_meal = sem_open("/meal", O_CREAT, 0644, 1)) == 0)
		return (1);
	sem_close(g_fork);
	sem_close(g_safe);
	sem_close(g_meal);
	sophos = sophos_sit_down(1, g_number_of_sophos);
	ret = launch_thread(sophos);
	sem_close(g_safe);
	unlink_sem();
	return (free_fct(&sophos, 0, ret));
}

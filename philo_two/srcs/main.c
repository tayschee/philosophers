/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbigot <tbigot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 11:00:55 by tbigot            #+#    #+#             */
/*   Updated: 2020/11/07 22:42:54 by tbigot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void		sophos_think(t_sophos *sophos)
{
	sophos_activity(sophos->number, " is thinking\n", g_sophos_die);
}

static void		sophos_sleep(t_sophos *sophos)
{
	sophos_activity(sophos->number, " is sleeping\n", g_sophos_die);
	usleep(1000 * g_time_to_sleep);
	sophos_think(sophos);
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
			sem_wait(&g_safe);
			gettimeofday(&sophos->last_meal, NULL);
			sem_post(&g_safe);
			sophos_activity(sophos->number, " is eating\n", g_sophos_die);
			usleep(1000 * g_time_to_eat);
			put_fork(sophos);
			if (sophos->eat_max != -1 && --sophos->eat_max == 0)
				return (NULL);
			sophos_sleep(sophos);
		}
	}
	return (NULL);
}

static int		launch_thread(t_sophos *sophos)
{
	int			i;
	int			ret;
	pthread_t	*tid;
	t_sophos	*save;

	i = -1;
	save = sophos;
	if (!(tid = malloc(sizeof(pthread_t) * (g_number_of_sophos + 1))))
		return (free_fct(&sophos, NULL, 1));
	gettimeofday(&g_begin, NULL);
	while (++i < g_number_of_sophos)
	{
		gettimeofday(&sophos->last_meal, NULL);
		if ((ret = pthread_create(&tid[i], NULL, eat, (void *)sophos)))
			return (free_fct(&sophos, tid, 1));
		sophos = sophos->next;
	}
	if ((ret = pthread_create(&tid[i], NULL, sophos_is_alive, (void *)save)))
		return (free_fct(&sophos, tid, 1));
	pthread_join(tid[i], NULL);
	while (--i >= 0)
		pthread_detach(tid[i]);
	free(tid);
	return (0);
}

int				main(int argc, char **argv)
{
	t_sophos		*sophos;
	int				ret;

	g_sophos_die = 1;
	if (check_argv(argc, argv))
	{
		ft_putstr("Les philosophes ne peuvent pas se reunir\n");
		return (1);
	}
	link_sem();
	if ((g_safe = sem_open("count", O_CREAT, 0644, g_number_of_sophos)) != 0)
		return (1);
	if ((g_fork = sem_open("fork", O_CREAT, 0644, g_number_of_sophos)) != 0)
		return (1);
	if ((g_meal = sem_open("fork2", O_CREAT | O_EXCL, 0644, (int)
	(g_number_of_sophos * 0.5))) != 0)
		return (1);
	sophos = sophos_sit_down(1, g_number_of_sophos);
	ret = launch_thread(sophos);
	if (ret == 0)
		free_fct(&sophos, NULL, 0);
	sem_close(g_semaphore);
	sem_close(g_meal);
	link_sem();
	return (ret);
}

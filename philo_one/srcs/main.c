/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbigot <tbigot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 11:00:55 by tbigot            #+#    #+#             */
/*   Updated: 2020/11/08 11:54:54 by tbigot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int		mutex()
{
	int i;

	i = -1;
	if (!(g_mutex = malloc(sizeof(pthread_mutex_t) * g_number_of_sophos)))
		return (1);
	if (!(g_safe = malloc(sizeof(pthread_mutex_t) * g_number_of_sophos)))
		return (1);
	while (++i < g_number_of_sophos)
	{
		pthread_mutex_init(&g_mutex[i], NULL);
		pthread_mutex_init(&g_safe[i], NULL);
	}
	return (0);
}

static void		sophos_sleep(t_sophos *sophos)
{
	sophos_activity(sophos->number, " is sleeping\n", g_sophos_die);
	usleep(1000 * g_time_to_sleep);
	sophos_activity(sophos->number, " is thinking\n", g_sophos_die);
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
			pthread_mutex_lock(&g_safe[sophos->number - 1]);
			gettimeofday(&sophos->last_meal, NULL);
			pthread_mutex_unlock(&g_safe[sophos->number - 1]); 
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
	void		*safe;

	i = -1;
	save = sophos;
	if (!(tid = malloc(sizeof(pthread_t) * (g_number_of_sophos + 1))))
		exit(free_fct(&sophos, NULL, 1));
	gettimeofday(&g_begin, NULL);
	while (++i < g_number_of_sophos)
	{
		gettimeofday(&sophos->last_meal, NULL);
		if ((ret = pthread_create(&tid[i], NULL, eat, (void *)sophos)))
			exit(free_fct(&sophos, tid, 1));
		sophos = sophos->next;
	}
	if ((ret = pthread_create(&tid[i], NULL, sophos_is_alive, (void *)save)))
		exit(free_fct(&sophos, tid, 1));
	pthread_join(tid[i], &safe);
	pthread_mutex_unlock((pthread_mutex_t *)safe);
	while (--i >= 0)
		pthread_detach(tid[i]);
	free(tid);
	return (0);
}

int				main(int argc, char **argv)
{
	t_sophos		*sophos;
	int				ret;
	
	ret = 0;
	if (check_argv(argc, argv))
	{
		ft_putstr("Les philosophes ne peuvent pas se reunir\n");
		return (1);
	}
	g_sophos_die = 1;
	if (mutex())
		return (1);
	sophos = sophos_sit_down(1, g_number_of_sophos);
	put_fork_on_table(sophos);
	ret = launch_thread(sophos);
	free_fct(&sophos, NULL, 0);
	while (--g_number_of_sophos >= 0)
	{
		pthread_mutex_destroy(&g_mutex[g_number_of_sophos]);
		pthread_mutex_destroy(&g_safe[g_number_of_sophos]);
	}
	return (ret);
}

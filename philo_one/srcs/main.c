/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbigot <tbigot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 11:00:55 by tbigot            #+#    #+#             */
/*   Updated: 2020/11/20 16:02:16 by tbigot           ###   ########.fr       */
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
	pthread_mutex_init(&g_write, NULL);
	return (0);
}

static void		sophos_sleep(t_sophos *sophos)
{
	(void)sophos;
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
		if ((sophos->handr && sophos->handl) || sophos->hand == 2 || 1)
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
	pthread_t	*tid;
	int			ret;
	t_sophos	*save;

	i = -1;
	save = sophos;
	if (!(tid = malloc(sizeof(pthread_t) * (g_number_of_sophos /** 2*/))))
		exit(free_fct(&sophos, NULL, 1));
	gettimeofday(&g_begin, NULL);
	if ((ret = sophos_pair(sophos, tid)))
		return (ret);
	if ((ret = sophos_impair(sophos, tid)))
		return (ret);
	/*while(++i < g_number_of_sophos)
		pthread_join(tid[i + g_number_of_sophos], NULL);*/
	sophos_is_alive(save);
	while (++i < g_number_of_sophos)
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

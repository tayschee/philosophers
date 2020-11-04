/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbigot <tbigot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 11:00:55 by tbigot            #+#    #+#             */
/*   Updated: 2020/11/03 16:37:33 by tbigot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void		sophos_think(t_sophos *sophos)
{
	pthread_mutex_lock(&g_mutex);
	sophos_activity(sophos->number, "is thinking\n");
	pthread_mutex_unlock(&g_mutex);
}

static void		sophos_sleep(t_sophos *sophos)
{
	pthread_mutex_lock(&g_mutex);
	sophos_activity(sophos->number, "is sleeping\n");
	pthread_mutex_unlock(&g_mutex);
	usleep(g_time_to_sleep * 1000);
	sophos_think(sophos);
}

void	*eat(void *sophos_pointer)
{
	t_sophos	*sophos;
	
	sophos = (t_sophos *)sophos_pointer;
	while (1)
	{
		take_fork(sophos);
		if (sophos->hand == 2)
		{
			pthread_mutex_lock(&g_mutex);
			sophos_activity(sophos->number, "is eating\n");
			pthread_mutex_unlock(&g_mutex);
			gettimeofday(&sophos->last_meal, NULL);
			usleep(g_time_to_eat * 1000);
			put_fork(sophos);
			if (sophos->eat_max != -1 && --sophos->eat_max == 0)
				return (NULL);
			sophos_sleep(sophos);
		}
	}
	return NULL;
}

static int launch_thread(t_sophos *sophos)
{
	int			i;
	int			ret;
	pthread_t	*tid;
	t_sophos	*save;

	i = -1;
	save = sophos;
	if (!(tid = malloc(sizeof(pthread_t) * g_number_of_sophos + 1)))
		exit(free_fct(&sophos, NULL, 1));
	gettimeofday(&g_begin, NULL);
	while(++i < g_number_of_sophos)
	{
		gettimeofday(&sophos->last_meal, NULL);
		if ((ret = pthread_create(&tid[i], NULL, eat, (void *)sophos)))
			exit(free_fct(&sophos, tid, 1));
		sophos = sophos->next;
	}
	if ((ret = pthread_create(&tid[i], NULL, sophos_is_alive, (void *)save)))
		exit(free_fct(&sophos, tid, 1));
	pthread_join(tid[i], NULL);
	while(--i >= 0)
		pthread_detach(tid[i]);
	free(tid);
	return (0);
}

int main(int argc, char **argv)
{
	t_sophos		*sophos;
	int				ret;

	ret = 0;
	if (check_argv(argc, argv))
	{
		ft_putstr("Les philosophes ne peuvent pas se reunir\n");
		return (1);
	}
	pthread_mutex_init(&g_mutex, NULL);
	sophos = sophos_sit_down(1, g_number_of_sophos);
	put_fork_on_table(sophos);
	ret = launch_thread(sophos);
	free_fct(&sophos, NULL, 0);
	pthread_mutex_destroy(&g_mutex);
	return (ret);
}
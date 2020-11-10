/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbigot <tbigot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 11:00:55 by tbigot            #+#    #+#             */
/*   Updated: 2020/11/10 14:35:51 by tbigot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int		mutex(void)
{
	int i;
	char *safe;

	i = -1;
	if ((g_write = sem_open("write", O_CREAT, 0644, 1)) == 0)
		return (1);
	if ((g_fork = sem_open("fork", O_CREAT, 0644, g_number_of_sophos)) == 0)
		return (2);
	if ((g_meal = sem_open("meal", O_CREAT, 0644, (int)
	(g_number_of_sophos * 0.5))) == 0)
		return (3);
	if (!(g_safe = malloc(sizeof(sem_t *))))
		return (4); 
	while (++i < g_number_of_sophos)
	{
		if (!(safe = name_sem(i)))
				return (4 + i);
		if ((g_safe[i] = sem_open(safe, O_CREAT, 0644, 1)) == 0)
		{
			free(safe);
			return (4 + i);
		}
		free(safe);
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
			sem_wait(g_safe[sophos->number - 1]);
			gettimeofday(&sophos->last_meal, NULL);
			sem_post(g_safe[sophos->number - 1]);
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
	
	i = -1;
	if (!(tid = malloc(sizeof(pthread_t) * (g_number_of_sophos * 2))))
		return (free_fct(&sophos, NULL, 1));
	gettimeofday(&g_begin, NULL);
	while (++i < g_number_of_sophos)
	{
		gettimeofday(&sophos->last_meal, NULL);
		if ((ret = pthread_create(&tid[i], NULL, eat, (void *)sophos)))
			return (free_fct(&sophos, tid, 1));
		if ((ret = pthread_create(&tid[i + g_number_of_sophos], NULL, sophos_is_alive, (void *)sophos)))
			return (free_fct(&sophos, tid, 1));
		sophos = sophos->next;
	}
	while(--i >= 0)
		pthread_join(tid[i + g_number_of_sophos], NULL);
	while (++i < g_number_of_sophos)
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
	sophos = sophos_sit_down(1, g_number_of_sophos);
	if ((ret = link_sem()))
	{
		close_sem(ret);
		link_sem();
		return (1);
	}
	if (mutex())
		free_fct(&sophos, NULL, 0);
	if (launch_thread(sophos))
		free_fct(&sophos, NULL, 0);
	close_sem(-1);
	if (link_sem())
		return (1);
	return (ret);
}

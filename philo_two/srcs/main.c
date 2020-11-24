/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbigot <tbigot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 11:00:55 by tbigot            #+#    #+#             */
/*   Updated: 2020/11/24 13:23:13 by tbigot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int		mutex(void)
{
	int		i;
	char	*safe;

	i = g_number_of_sophos;
	if ((g_write = sem_open("write", O_CREAT | O_EXCL, 0644, 1)) == 0)
		return (1);
	if (!(g_fork = sem_open("fork", O_CREAT | O_EXCL, 0644, i)))
		return (2);
	if ((g_meal = sem_open("meal", O_CREAT | O_EXCL, 0644, i * 0.5)) == 0)
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
			return (4 + i);
		}
		free(safe);
	}
	return (0);
}

void			ft_usleep(int sleep_time)
{
	t_val	begin;
	t_val	now;

	gettimeofday(&begin, NULL);
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

	sophos = (t_sophos *)sophos_pointer;
	while (g_sophos_die)
	{
		take_fork(sophos);
		sem_wait(g_safe[sophos->number - 1]);
		gettimeofday(&sophos->last_meal, NULL);
		sophos_activity(sophos->number, " is eating\n", g_sophos_die, 1);
		ft_usleep(g_time_to_eat);
		sem_post(g_safe[sophos->number - 1]);
		put_fork(sophos);
		if (sophos->eat_max != -1 && --sophos->eat_max == 0)
			return (NULL);
		sophos_activity(sophos->number, " is sleeping\n", g_sophos_die, 1);
		ft_usleep(g_time_to_sleep);
		sophos_activity(sophos->number, " is thinking\n", g_sophos_die, 1);
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
		if ((ret = pthread_create(&tid[i + g_number_of_sophos], NULL,
		sophos_is_alive, (void *)sophos)))
			return (free_fct(&sophos, tid, 1));
		sophos = sophos->next;
	}
	while (--i >= 0)
		pthread_join(tid[i + g_number_of_sophos], NULL);
	while (++i < g_number_of_sophos)
		pthread_join(tid[i], NULL);
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
	if (!launch_thread(sophos))
		free_fct(&sophos, NULL, 0);
	close_sem(-1);
	if (link_sem())
		return (1);
	return (ret);
}

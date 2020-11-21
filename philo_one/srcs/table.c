/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbigot <tbigot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 14:17:21 by tbigot            #+#    #+#             */
/*   Updated: 2020/11/20 16:05:29 by tbigot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void		sophos_is_alive(void *sophos_point)
{
	t_sophos	*sophos;
	t_sophos	*save;
	int			j;

	sophos = sophos_point;
	save = sophos;
	while (g_sophos_die)
	{
		while (sophos)
		{
			j = sophos->number - 1;
			pthread_mutex_lock(&g_safe[j]);
			if (is_die(sophos->last_meal) < 0 || sophos->eat_max == 0)
			{
				if (sophos->eat_max != 0 && g_sophos_die != 0)
				{
					g_sophos_die = 0;
					sophos_activity(sophos->number, " died\n", 1);
				}
				pthread_mutex_unlock(&g_safe[j]);
				return ;
			}
			pthread_mutex_unlock(&g_safe[j]);
			sophos = sophos->next;
		}
		sophos = save;
		usleep(4000);
	}
	return ;
}

void		put_fork_on_table(t_sophos *sophos)
{
	int			i;
	int			*fork;

	i = 0;
	if (!(fork = malloc(sizeof(int) * g_number_of_sophos)))
		free_fct(&sophos, NULL, 1);
	while (i < g_number_of_sophos)
		fork[i++] = 1;
	i = 0;
	while (sophos)
	{
		if (i == 0)
			sophos->f_left = &fork[g_number_of_sophos - 1];
		else
			sophos->f_left = &fork[i - 1];
		sophos->f_right = &fork[i++];
		sophos = sophos->next;
	}
}

t_sophos	*sophos_sit_down(int i, int nb)
{
	t_sophos	*sophos;

	if (i > nb || !(sophos = malloc(sizeof(t_sophos))))
		return (NULL);
	sophos->number = i;
	sophos->eat_max = g_eat_max;
	sophos->f_right = NULL;
	sophos->f_left = NULL;
	sophos->handr = 0;
	sophos->handl = 0;
	sophos->hand = 0;
	sophos->next = sophos_sit_down(++i, nb);
	return (sophos);
}

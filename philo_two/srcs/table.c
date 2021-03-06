/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbigot <tbigot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 14:17:21 by tbigot            #+#    #+#             */
/*   Updated: 2020/11/24 16:19:16 by tbigot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void		*sophos_is_alive(void *sophos_point)
{
	t_sophos	*sophos;

	sophos = sophos_point;
	while (g_sophos_die)
	{
		sem_wait(g_safe[sophos->number - 1]);
		if (is_die(sophos->last_meal) < 0 || sophos->eat_max == 0)
		{
			if (sophos->eat_max != 0)
			{
				sophos_activity(sophos->number, " died\n", 0);
				g_sophos_die = 0;
				sem_post(g_write);
			}
			sem_post(g_safe[sophos->number - 1]);
			return (NULL);
		}
		sem_post(g_safe[sophos->number - 1]);
		usleep(3000);
	}
	return (NULL);
}

t_sophos	*sophos_sit_down(int i, int nb)
{
	t_sophos	*sophos;

	if (i > nb || !(sophos = malloc(sizeof(t_sophos))))
		return (NULL);
	sophos->number = i;
	sophos->eat_max = g_eat_max;
	sophos->hand = 0;
	sophos->next = sophos_sit_down(++i, nb);
	return (sophos);
}

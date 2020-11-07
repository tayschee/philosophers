/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbigot <tbigot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 14:17:21 by tbigot            #+#    #+#             */
/*   Updated: 2020/11/07 22:44:37 by tbigot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void		*sophos_is_alive(void *sophos_point)
{
	t_sophos	*sophos;
	int			i;

	sophos = sophos_point;
	while (sophos)
	{
		i = 0;
		while (sophos)
		{
			i += sophos->eat_max != -1 && !sophos->eat_max ? 1 : 0;
			sem_wait(g_safe);
			if (is_die(sophos->last_meal) < 0 || (i == g_number_of_sophos))
			{
				g_sophos_die = 0;
				sem_post(g_safe);
				if (!(i == g_number_of_sophos && g_eat_max != -1))
					sophos_activity(sophos->number, " died\n", 1);
				return (NULL);
			}
			sem_post(g_safe);
			sophos = sophos->next;
		}
		sophos = sophos_point;
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

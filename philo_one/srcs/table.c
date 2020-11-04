/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbigot <tbigot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 14:17:21 by tbigot            #+#    #+#             */
/*   Updated: 2020/11/03 16:11:22 by tbigot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void		*sophos_is_alive(void *sophos_point)
{
	t_sophos	*sophos;
	t_sophos	*save;
	int			i;

	sophos = sophos_point;
	save = sophos;
	while (sophos)
	{
		i = 0;
		while (sophos)
		{
			if (sophos->eat_max != -1 && !sophos->eat_max)
				i++;
			if (is_die(sophos->last_meal) < 0 || (i == g_number_of_sophos
			&& g_eat_max != -1))
			{
				pthread_mutex_lock(&g_mutex);
					if (is_die(sophos->last_meal) < 0)
				sophos_activity(sophos->number, "died\n");
				return (NULL);
			}
			sophos = sophos->next;
		}
		sophos = save;
	}
	return (NULL);
}

void		put_fork_on_table(t_sophos *sophos)
{
	int			i;
	int			*fork;
	
	i = 0;
	if (!(fork = malloc(sizeof(int) * g_number_of_sophos))) // - 1
		exit(1); // fct_free
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
	int			fork;

	fork = 1;
	if (i > nb || !(sophos = malloc(sizeof(t_sophos))))
		return (NULL);
	sophos->number = i;
	sophos->eat_max = g_eat_max;
	sophos->f_right = NULL;
	sophos->f_left = NULL;
	sophos->hand = 0;
	//sophos->last_meal = NULL;
	sophos->next = sophos_sit_down(++i, nb);
	return (sophos);

}
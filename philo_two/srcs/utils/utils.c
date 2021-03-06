/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbigot <tbigot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 14:21:48 by tbigot            #+#    #+#             */
/*   Updated: 2020/11/24 16:29:27 by tbigot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void		close_sem(int i)
{
	int		j;

	j = -1;
	if (i > 1 || i < 0)
		sem_close(g_write);
	if (i > 2 || i < 0)
		sem_close(g_fork);
	if (i > 3 || i < 0)
		sem_close(g_meal);
	while (++j < g_number_of_sophos)
	{
		if (j + 5 > i || i < 0)
			sem_close(g_safe[j]);
	}
	if (j > 4 || i == -1)
		free(g_safe);
}

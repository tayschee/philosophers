/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbigot <tbigot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 13:34:46 by tbigot            #+#    #+#             */
/*   Updated: 2020/11/07 20:57:03 by tbigot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int			take_fork(t_sophos *sophos, int hand)
{
	if (hand < 2)
	{
		sem_wait(g_semaphore);
		sophos_activity(sophos->number, " has taken a fork\n", g_sophos_die, 1);
		sophos_activity(sophos->number, " has taken a fork\n", g_sophos_die, 1);
		return (2);
	}
	return (0);
}

int			put_fork(t_sophos *sophos)
{
	(void)sophos;
	sem_post(g_semaphore);
	return (2);
}

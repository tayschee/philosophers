/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbigot <tbigot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 13:34:46 by tbigot            #+#    #+#             */
/*   Updated: 2020/11/05 15:44:38 by tbigot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void		take_fork(t_sophos *sophos)
{
	if (sophos->hand < 2)
	{
		sem_wait(g_semaphore);
		sophos->hand += 1;
		sophos_activity(sophos->number, " has taken a fork\n", g_sophos_die);
	}
	if (sophos->hand < 2)
	{
		sem_wait(g_semaphore);
		sophos->hand += 1;
		sophos_activity(sophos->number, " has taken a fork\n", g_sophos_die);
	}
}

void		put_fork(t_sophos *sophos)
{
	sophos->hand -= 2;
	sem_post(g_semaphore);
	sem_post(g_semaphore);
}

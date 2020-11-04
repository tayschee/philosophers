/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbigot <tbigot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 13:34:46 by tbigot            #+#    #+#             */
/*   Updated: 2020/11/04 19:30:40 by tbigot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void		take_fork(t_sophos *sophos)
{
	pthread_mutex_lock(&g_mutex);
	if ((*(sophos->f_right) && *(sophos->f_left)) ||
	(sophos->hand == 1 && *(sophos->f_right)))
	{
		*(sophos->f_right) -= 1;
		sophos_activity(sophos->number, "has taken a fork\n");
		pthread_mutex_unlock(&g_mutex);
		sophos->hand += 1;
	}
	else
		pthread_mutex_unlock(&g_mutex);
	pthread_mutex_lock(&g_mutex);
	if ((*(sophos->f_left) && *(sophos->f_right)) ||
	(sophos->hand == 1 && *(sophos->f_left)))
	{
		*(sophos->f_left) -= 1;
		sophos_activity(sophos->number, "has taken a fork\n");
		pthread_mutex_unlock(&g_mutex);
		sophos->hand += 1;
	}
	else
		pthread_mutex_unlock(&g_mutex);
}

void		put_fork(t_sophos *sophos)
{
	sophos->hand -= 2;
	pthread_mutex_lock(&g_mutex);
	*(sophos->f_right) += 1;
	*(sophos->f_left) += 1;
	pthread_mutex_unlock(&g_mutex);
}

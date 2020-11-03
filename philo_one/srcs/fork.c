/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbigot <tbigot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 13:34:46 by tbigot            #+#    #+#             */
/*   Updated: 2020/11/03 16:50:52 by tbigot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void		take_fork(t_sophos *sophos, int put_or_take)
{
		if (put_or_take < 0)
		{
			pthread_mutex_lock(&g_mutex);
			if (*(sophos->f_right) && (*(sophos->f_left) || sophos->hand == 1))
			{
				*(sophos->f_right) += put_or_take;
				sophos_activity(sophos->number, "has taken a fork\n");
				sophos->hand -= put_or_take;
			}
			pthread_mutex_unlock(&g_mutex);
			pthread_mutex_lock(&g_mutex);
			if (*(sophos->f_left) && (*(sophos->f_right) || sophos->hand == 1))
			{
				*(sophos->f_left) += put_or_take;
				sophos_activity(sophos->number, "has taken a fork\n");
				sophos->hand -= put_or_take;
			}
			pthread_mutex_unlock(&g_mutex);
		}
		else
		{
			sophos->hand -= 2 * put_or_take;
			pthread_mutex_lock(&g_mutex);
			*(sophos->f_right) += put_or_take;
			*(sophos->f_left) += put_or_take;
			pthread_mutex_unlock(&g_mutex);
		}
}

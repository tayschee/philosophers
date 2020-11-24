/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbigot <tbigot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 13:34:46 by tbigot            #+#    #+#             */
/*   Updated: 2020/11/24 15:28:02 by tbigot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void		take_fork(t_sophos *sophos)
{
	int i;

	i = sophos->number != g_number_of_sophos ? sophos->number : 0;
	pthread_mutex_lock(&g_mutex[sophos->fork1]);
	sophos_activity(sophos->number, " has taken a fork\n", 1);
	pthread_mutex_lock(&g_mutex[sophos->fork2]);
	sophos_activity(sophos->number, " has taken a fork\n", 1);
}

void		put_fork(t_sophos *sophos)
{
	pthread_mutex_unlock(&g_mutex[sophos->fork1]);
	pthread_mutex_unlock(&g_mutex[sophos->fork2]);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbigot <tbigot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 16:29:11 by tbigot            #+#    #+#             */
/*   Updated: 2020/11/23 21:27:41 by tbigot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		pid_fct(t_sophos *sophos, pid_t *pid)
{
	pthread_t	tid;

	*pid = fork();
	gettimeofday(&sophos->last_meal, NULL);
	if (!*pid)
	{
		//g_fork = sem_open("/fork", O_RDWR);
		//g_safe = sem_open("/protect", O_RDWR);
		//g_meal = sem_open("/meal", O_RDWR);
		pthread_create(&tid, NULL, sophos_is_alive, (void *)sophos);
		pthread_detach(tid);
		eat((void *)sophos);
	}
	return (*pid);
}

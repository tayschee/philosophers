/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbigot <tbigot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 16:29:11 by tbigot            #+#    #+#             */
/*   Updated: 2020/11/24 12:58:37 by tbigot           ###   ########.fr       */
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
		pthread_create(&tid, NULL, sophos_is_alive, (void *)sophos);
		pthread_detach(tid);
		eat((void *)sophos);
	}
	return (*pid);
}

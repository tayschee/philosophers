/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbigot <tbigot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 16:29:11 by tbigot            #+#    #+#             */
/*   Updated: 2020/11/25 14:16:25 by tbigot           ###   ########.fr       */
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

void	*kill_everything(void *pointer)
{
	int i;
	int *pid;

	i = -1;
	pid = pointer;
	sem_wait(g_kill);
	while (++i < g_number_of_sophos && g_sophos_die == 1)
		kill(pid[i], SIGKILL);
	return (NULL);
}

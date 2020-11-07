/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbigot <tbigot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 16:29:11 by tbigot            #+#    #+#             */
/*   Updated: 2020/11/07 18:10:47 by tbigot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		pid_fct(t_sophos *sophos, pid_t *pid)
{
	*pid = fork();
	gettimeofday(&sophos->last_meal, NULL);
	if (!*pid)
		eat((void *)sophos);
	return (*pid);
}

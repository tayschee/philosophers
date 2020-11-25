/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbigot <tbigot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 13:34:46 by tbigot            #+#    #+#             */
/*   Updated: 2020/11/24 11:52:53 by tbigot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int			take_fork(int i)
{
	sem_wait(g_meal);
	sem_wait(g_fork);
	sophos_activity(i, " has taken a fork\n", 1);
	sem_wait(g_fork);
	sem_post(g_meal);
	sophos_activity(i, " has taken a fork\n", 1);
	return (0);
}

int			put_fork(void)
{
	sem_post(g_fork);
	sem_post(g_fork);
	return (0);
}

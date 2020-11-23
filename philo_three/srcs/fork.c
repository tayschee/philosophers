/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbigot <tbigot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 13:34:46 by tbigot            #+#    #+#             */
/*   Updated: 2020/11/10 10:30:36 by tbigot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int			take_fork(t_sophos *sophos)
{
	sem_wait(g_meal);
	sem_wait(g_fork);
	sophos_activity(sophos->number, " has taken a fork\n", g_sophos_die, 1);
	sem_wait(g_fork);
	sem_post(g_meal);
	sophos_activity(sophos->number, " has taken a fork\n", g_sophos_die, 1);
	return (0);
}

int			put_fork(void)
{
	sem_post(g_fork);
	sem_post(g_fork);
	return (0);
}

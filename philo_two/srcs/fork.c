/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbigot <tbigot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 13:34:46 by tbigot            #+#    #+#             */
/*   Updated: 2020/11/23 17:03:08 by tbigot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void		take_fork(t_sophos *sophos)
{
	sem_wait(g_meal);
	sem_wait(g_fork);
	sem_wait(g_fork);
	sem_post(g_meal);
	sophos_activity(sophos->number, " has taken a fork\n", g_sophos_die);
	sophos_activity(sophos->number, " has taken a fork\n", g_sophos_die);
}

void		put_fork(void)
{
	sem_post(g_fork);
	sem_post(g_fork);
}

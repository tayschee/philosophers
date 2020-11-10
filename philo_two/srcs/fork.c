/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbigot <tbigot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 13:34:46 by tbigot            #+#    #+#             */
/*   Updated: 2020/11/10 14:24:15 by tbigot           ###   ########.fr       */
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
	sophos->hand = 2;
}

void		put_fork(t_sophos *sophos)
{
	sem_post(g_fork);
	sem_post(g_fork);
	sophos->hand = 0;
}

void		close_sem(int i)
{
	//int		j;

	//j = -1;
	if (i > 1 || i < 0)
		sem_close(g_write);
	if (i > 2 || i < 0)
		sem_close(g_fork);
	if (i > 3 || i < 0)
		sem_close(g_meal);
	printf("%d\n", g_number_of_sophos);
	/*while (++j < g_number_of_sophos)
	{
		//if (j + 4 > i || i < 0)
		printf("2\n");
		sem_close(g_safe[j]);
	}*/
	free(g_safe);
}

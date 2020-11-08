/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbigot <tbigot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 13:34:46 by tbigot            #+#    #+#             */
/*   Updated: 2020/11/08 16:28:34 by tbigot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*void		take_fork(t_sophos *sophos)
{
	int	fork;

	fork = sophos->number - 1;
	pthread_mutex_lock(&g_mutex[fork]);
	if ((*(sophos->f_right) && *(sophos->f_left)) ||
	(sophos->hand == 1 && *(sophos->f_right)))
	{
		*(sophos->f_right) -= 1;
		pthread_mutex_unlock(&g_mutex[fork]);
		sophos_activity(sophos->number, " has taken a fork\n", g_sophos_die);
		sophos->hand += 1;
	}
	else
		pthread_mutex_unlock(&g_mutex[fork]);
	fork = sophos->number == 1 ? g_number_of_sophos - 1 : sophos->number - 2;
	pthread_mutex_lock(&g_mutex[fork]);
	if ((*(sophos->f_right) && *(sophos->f_left)) ||
	(sophos->hand == 1 && *(sophos->f_left)))
	{
		*(sophos->f_left) -= 1;
		pthread_mutex_unlock(&g_mutex[fork]);
		sophos_activity(sophos->number, " has taken a fork\n", g_sophos_die);
		sophos->hand += 1;
	}
	else
		pthread_mutex_unlock(&g_mutex[fork]);
}*/
void		take_other_fork(t_sophos *sophos)
{
	int fork;
	
	if (sophos->handl == 0)
	{
		fork = sophos->number == 1 ? g_number_of_sophos - 1 : sophos->number - 2;
		pthread_mutex_lock(&g_mutex[fork]);
		if ((*(sophos->f_right) && *(sophos->f_left)) ||
		(sophos->handr == 1 && *(sophos->f_left)))
		{
			*(sophos->f_left) = 0;
			pthread_mutex_unlock(&g_mutex[fork]);
			sophos_activity(sophos->number, " has taken a fork\n", g_sophos_die);
			sophos->handl = 1;
		}
		else
			pthread_mutex_unlock(&g_mutex[fork]);
	}
}

void		take_fork(t_sophos *sophos)
{
	int	fork;

	if (sophos->handr == 0)
	{
		fork = sophos->number - 1;
		pthread_mutex_lock(&g_mutex[fork]);
		if ((*(sophos->f_right) && *(sophos->f_left)) ||
		(sophos->handl == 1 && *(sophos->f_right)))
		{
			*(sophos->f_right) = 0;
			pthread_mutex_unlock(&g_mutex[fork]);
			sophos_activity(sophos->number, " has taken a fork\n", g_sophos_die);
			sophos->handr = 1;
		}
		else
			pthread_mutex_unlock(&g_mutex[fork]);
	}
	take_other_fork(sophos);
}

void		put_fork(t_sophos *sophos)
{
	int fork;

	fork = g_number_of_sophos - 1;
	pthread_mutex_lock(&g_mutex[fork]);
	*(sophos->f_right) = 1;
	pthread_mutex_unlock(&g_mutex[fork]);
	fork = sophos->number == 1 ? g_number_of_sophos - 1 : sophos->number - 2;
	pthread_mutex_lock(&g_mutex[fork]);
	*(sophos->f_left) = 1;
	pthread_mutex_unlock(&g_mutex[fork]);
	sophos->handr = 0;
	sophos->handl = 0;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fct_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbigot <tbigot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 13:38:35 by tbigot            #+#    #+#             */
/*   Updated: 2020/11/21 14:14:47 by tbigot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		is_die(t_val last_meal)
{
	t_val timer;

	timer = time_past(last_meal);
	return (g_time_to_die - convert_sec_to_msec(timer.tv_sec, timer.tv_usec));
}

void	sophos_activity(int nb, char *txt, int f)
{
	t_val	t;
	unsigned int time;

	pthread_mutex_lock(&g_write);
	if (f)
	{
		pthread_mutex_unlock(&g_write);
		t = time_past(g_begin);
		time = convert_sec_to_msec(t.tv_sec, t.tv_usec);
		//je pourrais calculer moi meme la taille de strlen
		ft_itoa(time, nb, txt, nb_chiffre(time) + 1 + nb_chiffre(nb) + ft_strlen(txt));
	}
	else
		pthread_mutex_unlock(&g_write);
	
}

int		check_argv(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (1);
	if ((g_number_of_sophos = (int)ft_atoi(argv[1])) < 2)
		return (1);
	if ((g_time_to_die = ft_atoi(argv[2])) <= 0)
		return (1);
	if ((g_time_to_eat = ft_atoi(argv[3])) < 0 && g_time_to_eat > 2147483)
		return (1);
	//g_time_to_eat *= 1000;
	if ((g_time_to_sleep = ft_atoi(argv[4])) < 0 && g_time_to_sleep > 2147483)
		return (1);
	//g_time_to_sleep *= 1000;
	if (argc == 6)
	{
		if ((g_eat_max = (int)ft_atoi(argv[5])) <= 0)
			return (1);
	}
	else
		g_eat_max = -1;
	return (0);
}

int		convert_sec_to_msec(time_t sec, suseconds_t usec)
{
	long	sec_convert;

	sec_convert = sec * 1000 + usec * 0.001;
	return (sec_convert);
}

t_val	time_past(t_val begin_timer)
{
	t_val	now;

	gettimeofday(&now, 0);
	now.tv_sec = now.tv_sec - begin_timer.tv_sec;
	now.tv_usec = (int)(now.tv_usec - begin_timer.tv_usec);
	if (now.tv_usec < 0)
	{
		now.tv_usec = 1000000 + now.tv_usec;
		now.tv_sec -= 1;
	}
	return (now);
}

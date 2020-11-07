/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fct_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbigot <tbigot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 13:38:35 by tbigot            #+#    #+#             */
/*   Updated: 2020/11/07 22:30:35 by tbigot           ###   ########.fr       */
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
	t_val	timer;
	char	*sophos_nb;
	char	*nb_timer;
	char	*join;

	if (f)
	{
		timer = time_past(g_begin);
		nb_timer = ft_itoa(convert_sec_to_msec(timer.tv_sec, timer.tv_usec));
		join = ft_strjoin(nb_timer, " ");
		if (nb_timer)
			free(nb_timer);
		sophos_nb = ft_itoa(nb);
		nb_timer = ft_strjoin(join, sophos_nb);
		if (join)
			free(join);
		if (sophos_nb)
			free(sophos_nb);
		join = ft_strjoin(nb_timer, txt);
		if (join)
		{
			ft_putstr(join);
			free(join);
		}
	}
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
	if ((g_time_to_sleep = ft_atoi(argv[4])) < 0 && g_time_to_sleep > 2147483)
		return (1);
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

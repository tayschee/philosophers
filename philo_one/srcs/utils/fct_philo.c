/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fct_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbigot <tbigot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 13:38:35 by tbigot            #+#    #+#             */
/*   Updated: 2020/11/03 16:51:28 by tbigot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

suseconds_t	is_die(t_val last_meal)
{
	t_val timer;

	timer = time_past(last_meal);
	return (g_time_to_die - convert_sec_to_usec(timer.tv_sec, timer.tv_usec));

}

void		sophos_activity(int nb, char *txt)
{
	t_val timer;

	timer = time_past(g_begin);
	ft_putnbr((int)convert_sec_to_usec(timer.tv_sec, timer.tv_usec));
	ft_putstr(" ");
	ft_putnbr(nb);
	ft_putstr(" ");
	ft_putstr(txt);
}

int				check_argv(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (1);
	if ((g_number_of_sophos = (int)ft_atosu(argv[1])) < 2)
		return (1);
	if ((g_time_to_die = ft_atosu(argv[2])) <= 0)
		return (1);
	if ((g_time_to_eat = ft_atosu(argv[3])) < 0)
		return (1);
	if ((g_time_to_sleep = ft_atosu(argv[4])) < 0)
		return (1);
	if (argc == 6)
	{
		if ((g_eat_max = (int)ft_atosu(argv[5])) <= 0)
			return (1);
	}
	else
		g_eat_max = -1;
	return (0);
}

suseconds_t		convert_sec_to_usec(time_t sec, suseconds_t usec)
{
	suseconds_t	sec_convert;

	sec_convert = sec * 1000000 + usec;
	return (sec_convert);
}

t_val	time_past(t_val begin_timer)
{
	t_val	now;

	gettimeofday(&now, 0);
	now.tv_sec = now.tv_sec - begin_timer.tv_sec;
	now.tv_usec = now.tv_usec - begin_timer.tv_usec;
	if (now.tv_usec < 0)
	{
		now.tv_usec = 10000000 - now.tv_usec;
		now.tv_sec -= 1;
	}
	return (now);
}
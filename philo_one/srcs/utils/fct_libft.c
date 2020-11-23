/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fct_libft.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbigot <tbigot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 13:38:51 by tbigot            #+#    #+#             */
/*   Updated: 2020/11/23 16:27:24 by tbigot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int				ft_atoi(const char *str)
{
	int			i;
	int			sign;
	int			value;

	i = 0;
	value = 0;
	sign = 1;
	while (str[i] == 32 || (str[i] >= 8 && str[i] <= 13))
		i++;
	if (str[i] == '+')
	{
		i++;
	}
	else if (str[i] == '-')
	{
		i++;
		sign = -1;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		value = value * 10 + str[i] - '0';
		i++;
	}
	value = value * sign;
	return (value);
}

int				ft_strlen(const char *txt)
{
	int	i;

	i = 0;
	while (txt && txt[i])
		i++;
	return (i);
}

void			ft_putstr(char *txt)
{
	write(1, txt, ft_strlen(txt));
}

unsigned int	nb_chiffre(unsigned int n)
{
	int i;

	i = 0;
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	if (i == 0)
		return (1);
	return (i);
}

void			ft_itoa(unsigned int time, unsigned int n,
				char *txt, unsigned int i)
{
	unsigned int			j;
	char					nb[i + 1];

	j = ft_strlen(txt);
	nb[i] = 0;
	while (j > 0)
		nb[--i] = txt[--j];
	if (n == 0)
		nb[--i] = '0';
	while (n > 0)
	{
		nb[--i] = (n % 10) + '0';
		n = n / 10;
	}
	nb[--i] = ' ';
	if (time == 0)
		nb[--i] = '0';
	while (time > 0)
	{
		nb[--i] = (time % 10) + '0';
		time = time / 10;
	}
	ft_putstr(nb);
}

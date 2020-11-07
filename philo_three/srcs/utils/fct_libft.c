/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fct_libft.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbigot <tbigot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 13:38:51 by tbigot            #+#    #+#             */
/*   Updated: 2020/11/06 17:27:34 by tbigot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		ft_atoi(const char *str)
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

int		ft_strlen(const char *txt)
{
	int	i;

	i = 0;
	while (txt && txt[i])
		i++;
	return (i);
}

void	ft_putstr(char *txt)
{
	write(1, txt, ft_strlen(txt));
}

void	ft_putnbr(int n)
{
	char		txt;
	long int	nb;

	nb = n;
	if (nb < 0)
	{
		nb = -nb;
		write(0, "-", 1);
	}
	if (nb > 9)
	{
		txt = nb % 10 + '0';
		nb = nb / 10;
		ft_putnbr(nb);
		write(0, &txt, 1);
	}
	else
	{
		txt = nb + '0';
		write(0, &txt, 1);
	}
}

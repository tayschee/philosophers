/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fct_libft.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbigot <tbigot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 13:38:51 by tbigot            #+#    #+#             */
/*   Updated: 2020/11/03 16:45:51 by tbigot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

suseconds_t		ft_atosu(const char *str)
{
	suseconds_t	i;
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

int		ft_strlen(char *txt)
{
	int	i;

	i = 0;
	while(txt && txt[i])
		i++;
	return (i);
}

void	ft_putstr(char *txt)
{
	write(1, txt, ft_strlen(txt));
}

void	ft_putnbr(long int n)
{
	char			txt;
	long long int	nb;

	nb = n;
	if (nb < 0)
	{
		nb = -nb;
		write(1, "-", 1);
	}
	if (nb > 9)
	{
		txt = nb % 10 + '0';
		nb = nb / 10;
		ft_putnbr(nb);
		write(1, &txt, 1);
	}
	else
	{
		txt = nb + '0';
		write(1, &txt, 1);
	}
}
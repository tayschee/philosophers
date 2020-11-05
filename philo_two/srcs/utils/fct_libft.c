/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fct_libft.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbigot <tbigot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 13:38:51 by tbigot            #+#    #+#             */
/*   Updated: 2020/11/05 15:41:40 by tbigot           ###   ########.fr       */
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

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*tab;
	int		i;
	int		j;
	int		size;

	i = 0;
	j = 0;
	if (!s1 && !s2)
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2);
	if (!(tab = ft_calloc((size + 1), sizeof(char))))
		return (NULL);
	while (s1 && s1[j])
	{
		tab[j] = s1[j];
		j++;
	}
	while (s2 && s2[i])
	{
		tab[i + j] = s2[i];
		i++;
	}
	return (tab);
}

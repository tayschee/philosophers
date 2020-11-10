/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fct_libft2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbigot <tbigot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 15:36:11 by tbigot            #+#    #+#             */
/*   Updated: 2020/11/10 14:44:13 by tbigot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	nb_chiffre(long int n)
{
	int i;

	i = 0;
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char		*ft_itoa(int n)
{
	int			i;
	char		*nb;
	long int	nbr;

	i = 0;
	nbr = n;
	if (n < 0)
	{
		i += 1;
		nbr = nbr * -1;
	}
	i += nb_chiffre(nbr);
	if (i == 0)
		i = 1;
	if (!(nb = (char *)ft_calloc(i + 1, sizeof(char))))
		return (NULL);
	nb[0] = '-';
	if (n == 0)
		nb[0] = '0';
	while (nbr > 0)
	{
		nb[--i] = (nbr % 10) + '0';
		nbr = nbr / 10;
	}
	return (nb);
}

void		*ft_calloc(size_t count, size_t size)
{
	size_t			i;
	unsigned char	*tab;

	i = 0;
	if (!(tab = malloc(size * count)))
		return (NULL);
	while (i < count)
	{
		tab[i] = '\0';
		i++;
	}
	return ((void *)tab);
}

int			link_sem(void)
{
	int		i;
	char	*name;

	i = -1;
	sem_unlink("fork");
	sem_unlink("meal");
	sem_unlink("write");
	while (++i < g_number_of_sophos)
	{
		if (!(name = name_sem(i)))
			return (1);
		sem_unlink(name);
		free(name);
	}
	return (0);
}

char		*name_sem(int i)
{
	char *merge;
	char *number;

	if (!(number = ft_itoa(i)))
		return (NULL);
	merge = ft_strjoin("safe", number);
	free(number);
	return (merge);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbigot <tbigot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 21:27:28 by tbigot            #+#    #+#             */
/*   Updated: 2020/11/24 12:52:18 by tbigot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	close_sem(int i)
{
	int j;

	j = -1;
	if (i > 1 || i == -1)
		sem_close(g_fork);
	if (i > 2 || i == -1)
		sem_close(g_meal);
	if (i > 3 || i == -1)
		sem_close(g_write);
	while (++j < g_number_of_sophos)
	{
		if (i > 4 + j || i == -1)
			sem_close(g_safe[j]);
	}
	if (i > 4 || i == -1)
		free(g_safe);
}

int		unlink_sem(void)
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

char	*name_sem(int i)
{
	char *merge;
	char *number;

	if (!(number = ft_itoa(i)))
		return (NULL);
	merge = ft_strjoin("safe", number);
	free(number);
	return (merge);
}

char	*ft_itoa(int n)
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
	if (!(nb = (char *)malloc((i + 1) * sizeof(char))))
		return (NULL);
	nb[i] = 0;
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
	if (!(tab = malloc((size + 1) * sizeof(char))))
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
	tab[i + j] = 0;
	return (tab);
}

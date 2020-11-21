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
	if (i == 0)
		i = 1;
	if (!(nb = (char *)malloc(i + 1 * sizeof(char))))
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

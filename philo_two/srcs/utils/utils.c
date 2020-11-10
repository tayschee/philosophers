/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbigot <tbigot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 14:21:48 by tbigot            #+#    #+#             */
/*   Updated: 2020/11/10 14:44:30 by tbigot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    ft_putnbr(int n)
{
        char            txt;
        long int        nb;

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

void		close_sem(int i)
{
	//int		j;

	//j = -1;
	if (i > 1 || i < 0)
		sem_close(g_write);
	if (i > 2 || i < 0)
		sem_close(g_fork);
	if (i > 3 || i < 0)
		sem_close(g_meal);
	printf("%d\n", g_number_of_sophos);
	/*while (++j < g_number_of_sophos)
	{
		//if (j + 4 > i || i < 0)
		printf("2\n");
		sem_close(g_safe[j]);
	}*/
	free(g_safe);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sophos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbigot <tbigot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 12:21:14 by tbigot            #+#    #+#             */
/*   Updated: 2020/11/24 16:42:20 by tbigot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int			sophos_impair(t_sophos *sophos, pthread_t *tid)
{
	int i;
	int	ret;

	i = 0;
	while (sophos)
	{
		gettimeofday(&sophos->last_meal, NULL);
		if ((ret = pthread_create(&tid[i], NULL, eat, (void *)sophos)))
			return (free_fct(&sophos, tid, 1));
		if ((ret = pthread_create(&tid[i + g_number_of_sophos], NULL,
		sophos_is_alive, (void *)sophos)))
			return (free_fct(&sophos, tid, 1));
		sophos = sophos->next;
		if (sophos)
			sophos = sophos->next;
		i += 2;
	}
	return (0);
}

int			sophos_pair(t_sophos *sophos, pthread_t *tid)
{
	int i;
	int ret;

	sophos = sophos->next;
	i = 1;
	while (sophos)
	{
		gettimeofday(&sophos->last_meal, NULL);
		if ((ret = pthread_create(&tid[i], NULL, eat, (void *)sophos)))
			return (free_fct(&sophos, tid, 1));
		if ((ret = pthread_create(&tid[i + g_number_of_sophos], NULL,
		sophos_is_alive, (void *)sophos)))
			return (free_fct(&sophos, tid, 1));
		sophos = sophos->next;
		if (sophos)
			sophos = sophos->next;
		i += 2;
	}
	return (0);
}

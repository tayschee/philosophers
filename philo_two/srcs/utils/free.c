/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbigot <tbigot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 14:37:40 by tbigot            #+#    #+#             */
/*   Updated: 2020/11/05 14:33:08 by tbigot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	free_fct(t_sophos **sophos, pthread_t *tid, int i)
{
	t_sophos	*last;
	t_sophos	*before;

	if (tid)
		free(tid);
	last = *sophos;
	while (sophos && *sophos)
	{
		before = NULL;
		while (last->next)
		{
			before = last;
			last = last->next;
		}
		if (before)
			before->next = NULL;
		if (!before)
			*sophos = NULL;
		free(last);
		last = *sophos;
	}
	return (i);
}

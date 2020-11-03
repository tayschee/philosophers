/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbigot <tbigot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 14:37:40 by tbigot            #+#    #+#             */
/*   Updated: 2020/11/03 16:35:05 by tbigot           ###   ########.fr       */
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
		{
			free(last);
			before->next = NULL;
		}
		else
		{
			free(last->f_right);
			free(last);
			*sophos = NULL;
		}
		last = *sophos;
	}
	return (i);
}
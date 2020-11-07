/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbigot <tbigot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 11:00:55 by tbigot            #+#    #+#             */
/*   Updated: 2020/11/07 20:49:23 by tbigot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void		sophos_think(t_sophos *sophos)
{
	sophos_activity(sophos->number, " is thinking\n", sophos->number, 1);
}

static void		sophos_sleep(t_sophos *sophos)
{
	sophos_activity(sophos->number, " is sleeping\n", sophos->number, 1);
	usleep(g_time_to_sleep * 1000);
	sophos_think(sophos);
}

void	*eat(void *sophos_pointer)
{
	int			hand;
	t_sophos	*sophos;
	pthread_t	tid;
	
	hand = 0;
	sophos = (t_sophos *)sophos_pointer;
	g_semaphore = sem_open("/fork", O_RDWR);
	g_protect = sem_open("/protect", O_RDWR);
	pthread_create(&tid, NULL, sophos_is_alive, (void *)sophos);
	pthread_detach(tid);
	while (g_sophos_die)
	{
		hand += take_fork(sophos, hand);
		if (hand == 2)
		{
			sem_wait(g_protect);
			gettimeofday(&sophos->last_meal, NULL);
			sophos_activity(sophos->number, " is eating\n", g_sophos_die, 0);
			sem_post(g_protect);
			usleep(g_time_to_eat * 1000);
			hand -= put_fork(sophos);
			if (sophos->eat_max != -1 && --sophos->eat_max == 0)
				break ;
			sophos_sleep(sophos);
		}
	}
	sem_wait(g_protect);
	exit(0);
}

int 	launch_thread(t_sophos *sophos)
{
	int			i;
	int			status;
	pid_t		pid[g_number_of_sophos];
	int			j;

	i = -1;
	j = 0;
	gettimeofday(&g_begin, NULL);
	while(++i < g_number_of_sophos)
	{
		if (pid_fct(sophos, &pid[i]) < 0)
			return (1);
		sophos = sophos->next;
	}
	g_protect = sem_open("/protect", O_RDWR);
	while(j < g_number_of_sophos && waitpid(-1, &status, 0) && WEXITSTATUS(status) == 0)
	{
		j++;
		sem_post(g_protect);
	}
	while(--i >= 0 && j < g_number_of_sophos)
		kill(pid[i], SIGINT);
	sem_post(g_protect);
	return (0);
}

int main(int argc, char **argv)
{
	t_sophos		*sophos;
	int				ret;

	ret = 0;
	g_sophos_die = 1;
	sem_unlink("/fork");
	sem_unlink("/protect");
	if (check_argv(argc, argv))
	{
		ft_putstr("Les philosophes ne peuvent pas se reunir\n");
		return (1);
	}
	if ((g_semaphore = sem_open("/fork", O_CREAT | O_EXCL, 0644, (int)(g_number_of_sophos / 2))) == SEM_FAILED)
		return (1);
	if ((g_protect = sem_open("/protect", O_CREAT | O_EXCL, 0644, 1)) == SEM_FAILED)
		return (1);
	sem_close(g_semaphore);
	sem_close(g_protect);
	sophos = sophos_sit_down(1, g_number_of_sophos);
	ret = launch_thread(sophos);
	sem_close(g_protect);
	sem_unlink("/protect");
	sem_unlink("/fork");
	return (free_fct(&sophos, 0, ret));
}
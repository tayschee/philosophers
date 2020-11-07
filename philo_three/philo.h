/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbigot <tbigot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 11:00:49 by tbigot            #+#    #+#             */
/*   Updated: 2020/11/07 20:51:50 by tbigot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <semaphore.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>

# define FORK "/fork"
# define PROTECT "/protect"

typedef struct timeval	t_val;

typedef struct			s_sophos
{
	int					number;
	int					eat_max;
	t_val				last_meal;
	int					hand;
	void				*next;
}						t_sophos;

t_val					g_begin;
int						g_sophos_die;
int						g_number_of_sophos;
int						g_time_to_die;
int						g_time_to_eat;
int						g_time_to_sleep;
int						g_eat_max;

sem_t					*g_semaphore;
sem_t					*g_protect;

t_val					time_past(t_val begin_timer);
int						convert_sec_to_msec(time_t sec, suseconds_t usec);
int						is_die(t_val last_meal);

int						ft_atoi(const char *str);
int						ft_strlen(const char *txt);
void					ft_putstr(char *txt);
void					ft_putnbr(int n);
char					*ft_strdup(const char *s1);

t_sophos				*sophos_sit_down(int i, int nb_sophos);
int						check_argv(int argc, char **argv);
void					*eat(void *sophos);
void					sophos_activity(int nb, char *txt, int f, int f2);
int						take_fork(t_sophos *sophos, int hand);
int						put_fork(t_sophos *sophos);
void					*sophos_is_alive(void *sophos_point);
int						free_fct(t_sophos **sophos, pid_t *pid, int i);
int						pid_fct(t_sophos *sophos, pid_t *pid);
int						launch_thread(t_sophos	*sophos);

#endif
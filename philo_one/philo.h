/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbigot <tbigot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 11:00:49 by tbigot            #+#    #+#             */
/*   Updated: 2020/11/03 16:46:24 by tbigot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO
# define PHILO

# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct timeval t_val;

typedef struct		s_sophos
{
	int				number;
	int				eat_max;
	t_val			last_meal;
	int				*f_right;
	int				*f_left;
	int				hand;
	struct s_sophos	*next;
}					t_sophos;

t_val			g_begin;
int				g_number_of_sophos;
suseconds_t		g_time_to_die;
suseconds_t		g_time_to_eat;
suseconds_t		g_time_to_sleep;
suseconds_t		g_eat_max;

pthread_mutex_t	g_mutex;

t_val			time_past(t_val begin_timer);
suseconds_t		convert_sec_to_usec(time_t sec, suseconds_t usec);
int				ft_strlen(char *txt);
void			ft_putstr(char *txt);
suseconds_t		tab_to_usec(char *arg);
suseconds_t		ft_atosu(const char *str);
t_sophos		*sophos_sit_down(int i, int nb_sophos);
int				check_argv(int argc, char **argv);
void			put_fork_on_table(t_sophos *sophos);
void			*eat(void *sophos);
void			ft_putnbr(long int n);
void			sophos_activity(int nb, char *txt);
void			take_fork(t_sophos *sophos, int put_or_take);
void			*sophos_is_alive(void *sophos_point);
suseconds_t		is_die(t_val last_meal);
int				free_fct(t_sophos **sophos, pthread_t *tid, int i);
#endif
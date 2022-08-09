/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayalman <ayalman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 19:41:37 by ayalman           #+#    #+#             */
/*   Updated: 2022/08/09 21:12:19 by ayalman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft/include/libft.h"
# include <stdbool.h>

typedef struct s_thread t_thread;

typedef struct	s_philosopher
{
	int				philosopher_id;
	long			time_since_eat;
	int				fork_r;
	int				fork_l;
	int				num_of_time_ate;
	int				all_eat;
	pthread_t		*philosopher;
	t_thread		*thread_main;
}	t_philosopher;

typedef struct	s_thread
{
	int						no_of_philosophers;
	int						time_of_eat;
	int						time_of_sleep;
	int						time_of_death;
	int						start_eat;
	int						all_should_eat;
	int						*array_philosophers;
	int						died;
	long					start_time;
	pthread_mutex_t			id_lock;
	pthread_mutex_t			**forks;
	t_philosopher			**philosophers;
}	t_thread;

//actions
void		printaction(t_philosopher *main, char *msg);
void		smart_sleep(int ms);
void		eat(t_philosopher *philos);
int			dead(t_thread *main);
void		*work(void *main_struct);

//control
bool		checker(int ac, char **av);

//init
void		philosopher_init(t_thread *ret);
t_thread	*create(char **av, bool arg_check);

//philosophers
void		thread_doer(t_thread *main);

//utilities
long		timestamp(void);
time_t		time_diff(time_t past, time_t present);
#endif
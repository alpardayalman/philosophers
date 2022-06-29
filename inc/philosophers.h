#ifndef _PHILOSOPHER_H
#define _PHILOSOPHER_H

#include <pthread.h>
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft/include/libft.h"
#include <stdbool.h>

struct	thread_t;

struct philosopher_t
{
	int philosopher_ID;
	long time_since_eat;
	int fork_r;
	int fork_l;
	int num_of_time_ate;
	int all_eat;
	pthread_t *philosopher;
	struct thread_t *thread_main;
};

struct thread_t
{
	int no_of_philosophers;
	int	time_of_eat;
	int time_of_sleep;
	int time_of_death;
	int start_eat;
	int all_should_eat;
	int *array_philosophers;
	int died;
	long startTime;
	pthread_mutex_t ID_lock;
	pthread_mutex_t **forks;
	struct philosopher_t **philosophers;
};

//actions
void	printAction(struct philosopher_t *main, char *msg);
void	smart_sleep(int ms);
void	eat(struct philosopher_t *philos);
int		dead(struct thread_t *main);
void	*work(void *main_struct);

//control
bool	checker(int ac, char **av);

//init
void	philosopher_init(struct thread_t *ret);
struct thread_t	*create(char **av, bool arg_check);

//philosophers
void	thread_doer(struct thread_t *main);

//utilities
long	timestamp(void);
time_t	time_diff(time_t past, time_t present);
#endif
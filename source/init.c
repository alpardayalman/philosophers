#include "../inc/philosophers.h"

void	philosopher_init(struct thread_t *ret)
{
	ret->philosophers = (struct philosopher_t **)malloc(sizeof(struct philosopher_t *) * ret->no_of_philosophers);
	ret->forks = (pthread_mutex_t **)malloc(sizeof(pthread_mutex_t *) * ret->no_of_philosophers);
	for (int i = 0; i < ret->no_of_philosophers; i++)
	{
		ret->forks[i] = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(ret->forks[i], NULL);
		ret->philosophers[i] = (struct philosopher_t *)malloc(sizeof(struct philosopher_t));
		ret->philosophers[i]->time_since_eat = 0;
		ret->philosophers[i]->fork_l = i;
		ret->philosophers[i]->fork_r = ((i + 1) % ret->no_of_philosophers);
		ret->philosophers[i]->philosopher_ID = i;
		ret->philosophers[i]->philosopher = (pthread_t *)malloc(sizeof(pthread_t));
		ret->philosophers[i]->thread_main = ret;
		ret->philosophers[i]->num_of_time_ate = 0;
	}
}

struct thread_t	*create(char **av, bool arg_check)
{
	struct thread_t *ret = (struct thread_t *)malloc(sizeof(struct thread_t));
	ret->no_of_philosophers = atoi(av[1]);
	ret->time_of_eat = atoi(av[3]);
	ret->time_of_sleep = atoi(av[4]);
	ret->time_of_death = atoi(av[2]);
	ret->startTime = timestamp();
	ret->died = 0;
	if (arg_check)
		ret->all_should_eat = atoi(av[5]);
	else
		ret->all_should_eat = -1;
	pthread_mutex_init(&ret->ID_lock, NULL);
	philosopher_init(ret);
	return (ret);
}
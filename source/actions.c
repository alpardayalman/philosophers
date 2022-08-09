#include "../inc/philosophers.h"

void	printAction(struct philosopher_t *main, char *msg)
{
	if (!main->thread_main->died)
	{
		pthread_mutex_lock(&main->thread_main->ID_lock);
		usleep(100);
		ft_printf("%i:ms ", timestamp() - main->thread_main->startTime);
		ft_printf("%i ", main->philosopher_ID);
		ft_printf("%s\n", msg);
		pthread_mutex_unlock(&main->thread_main->ID_lock);
	}
}

void	print_dead_action(struct philosopher_t *main, char *msg)
{
	main->thread_main->died = 1;
	pthread_mutex_lock(&main->thread_main->ID_lock);
	ft_printf("%i:ms ", timestamp() - main->thread_main->startTime);
	ft_printf("%i ", main->philosopher_ID);
	ft_printf("%s\n", msg);
}

void smart_sleep(int ms)
{
	long time = timestamp();
	usleep(ms*920);
	while (timestamp() < ms + time)
		usleep(ms*3);
}

void	eat(struct philosopher_t *philos)
{
	struct thread_t *main = philos->thread_main;
	if (philos->num_of_time_ate != main->all_should_eat && !main->died)
	{
		pthread_mutex_lock(main->forks[philos->fork_l]);
		printAction(philos, "has taken the left fork");
		pthread_mutex_lock(main->forks[philos->fork_r]);
		printAction(philos, "has taken the right fork");
		printAction(philos, "is eating");
		philos->num_of_time_ate++;
		philos->time_since_eat = timestamp();
		smart_sleep(philos->thread_main->time_of_eat);
		pthread_mutex_unlock(main->forks[philos->fork_l]);
		pthread_mutex_unlock(main->forks[philos->fork_r]);
	}
}

int	dead(struct thread_t *main)
{
	int	i;

	while (1)
	{
		i = -1;
		while (++i < main->no_of_philosophers)
		{
			if (main->philosophers[i]->num_of_time_ate == main->all_should_eat)
				return (1);
			if (timestamp() - main->philosophers[i % main->no_of_philosophers]->time_since_eat > main->time_of_death)
			{
				print_dead_action(main->philosophers[i % main->no_of_philosophers], "died");
				pthread_mutex_unlock(&main->ID_lock);
				return (1);
			}
		}
	}
	return (0);
}

void	*work(void *main_struct)
{
	struct philosopher_t *philos = (struct philosopher_t *)main_struct;
	struct thread_t *main = philos->thread_main;
	if (philos->philosopher_ID % 2 == 1)
		smart_sleep(100);
	while (!main->died && (philos->num_of_time_ate != main->all_should_eat))
	{
		eat(philos);
		if (philos->num_of_time_ate == main->all_should_eat)
		{
			printAction(philos, "ate all the food it was due.");
			return NULL;
		}
		printAction(philos, "is sleeping");
		smart_sleep(main->time_of_sleep);
		printAction(philos, "is thinking");
	}
	return NULL;
}
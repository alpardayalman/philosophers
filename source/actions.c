#include "../inc/philosophers.h"

void	printaction(t_philosopher *main, char *msg)
{
	if (!main->thread_main->died)
	{
		pthread_mutex_lock(&main->thread_main->id_lock);
		usleep(100);
		ft_printf("%i:ms ", timestamp() - main->thread_main->start_time);
		ft_printf("%i ", main->philosopher_id);
		ft_printf("%s\n", msg);
		pthread_mutex_unlock(&main->thread_main->id_lock);
	}
}

void	print_dead_action(t_philosopher *main, char *msg)
{
	main->thread_main->died = 1;
	pthread_mutex_lock(&main->thread_main->id_lock);
	ft_printf("%i:ms ", timestamp() - main->thread_main->start_time);
	ft_printf("%i ", main->philosopher_id);
	ft_printf("%s\n", msg);
}

void	smart_sleep(int ms)
{
	long time = timestamp();
	usleep(ms*920);
	while (timestamp() < ms + time)
		usleep(ms*3);
}

void	eat(t_philosopher *philos)
{
	t_thread *main = philos->thread_main;
	if (philos->num_of_time_ate != main->all_should_eat && !main->died)
	{
		pthread_mutex_lock(main->forks[philos->fork_l]);
		printaction(philos, "has taken the left fork");
		pthread_mutex_lock(main->forks[philos->fork_r]);
		printaction(philos, "has taken the right fork");
		printaction(philos, "is eating");
		philos->num_of_time_ate++;
		philos->time_since_eat = timestamp();
		smart_sleep(philos->thread_main->time_of_eat);
		pthread_mutex_unlock(main->forks[philos->fork_l]);
		pthread_mutex_unlock(main->forks[philos->fork_r]);
	}
}

int	dead(t_thread *main)
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
				pthread_mutex_unlock(&main->id_lock);
				return (1);
			}
		}
	}
	return (0);
}

void	*work(void *main_struct)
{
	t_philosopher *philos = (t_philosopher *)main_struct;
	t_thread *main = philos->thread_main;
	if (philos->philosopher_id % 2 == 1)
		smart_sleep(100);
	while (!main->died && (philos->num_of_time_ate != main->all_should_eat))
	{
		eat(philos);
		if (philos->num_of_time_ate == main->all_should_eat)
		{
			printaction(philos, "ate all the food it was due.");
			return NULL;
		}
		printaction(philos, "is sleeping");
		smart_sleep(main->time_of_sleep);
		printaction(philos, "is thinking");
	}
	return NULL;
}
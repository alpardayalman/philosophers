#include "../inc/philosophers.h"

void	thread_doer(struct thread_t *main)
{
	for (int i = 0; i < main->no_of_philosophers; i++)
	{
		pthread_create(main->philosophers[i]->philosopher, NULL, &work, (void *)main->philosophers[i]);
		main->philosophers[i]->time_since_eat = timestamp();
	}
	if (dead(main))
		return;
	for (int i = 0; i < main->no_of_philosophers; i++)
	{
		pthread_join(*main->philosophers[i]->philosopher, NULL);
		pthread_mutex_destroy(main->forks[i]);
	}
	pthread_mutex_destroy(&main->ID_lock);
}

int	main(int ac, char **av)
{
	bool	check_arg;
	check_arg = checker(ac, av);
	struct thread_t *main = create(av, check_arg);
	thread_doer(main);
	return 1;
}
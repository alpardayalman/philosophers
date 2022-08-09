/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ardayalman <ardayalman@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 22:57:13 by ardayalman        #+#    #+#             */
/*   Updated: 2022/08/09 23:09:13 by ardayalman       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	philosopher_init(t_thread *ret)
{
	int	i;

	i = -1;
	ret->philosophers = (t_philosopher **)malloc(sizeof(t_philosopher *) \
		* ret->no_of_philosophers);
	ret->forks = (pthread_mutex_t **)malloc(sizeof(pthread_mutex_t *) \
		* ret->no_of_philosophers);
	while (++i < ret->no_of_philosophers)
	{
		ret->forks[i] = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(ret->forks[i], NULL);
		ret->philosophers[i] = (t_philosopher *)malloc(sizeof(t_philosopher));
		ret->philosophers[i]->time_since_eat = 0;
		ret->philosophers[i]->fork_l = i;
		ret->philosophers[i]->fork_r = ((i + 1) % ret->no_of_philosophers);
		ret->philosophers[i]->philosopher_id = i;
		ret->philosophers[i]->philosopher = (pthread_t *)malloc \
			(sizeof(pthread_t));
		ret->philosophers[i]->thread_main = ret;
		ret->philosophers[i]->num_of_time_ate = 0;
	}
}

t_thread	*create(char **av, bool arg_check)
{
	t_thread	*ret;

	ret = (t_thread *)malloc(sizeof(t_thread));
	ret->no_of_philosophers = atoi(av[1]);
	ret->time_of_eat = atoi(av[3]);
	ret->time_of_sleep = atoi(av[4]);
	ret->time_of_death = atoi(av[2]);
	ret->start_time = timestamp();
	ret->died = 0;
	if (arg_check)
		ret->all_should_eat = atoi(av[5]);
	else
		ret->all_should_eat = -1;
	pthread_mutex_init(&ret->id_lock, NULL);
	philosopher_init(ret);
	return (ret);
}

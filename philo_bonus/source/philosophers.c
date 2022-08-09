/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ardayalman <ardayalman@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 23:02:06 by ardayalman        #+#    #+#             */
/*   Updated: 2022/08/09 23:07:04 by ardayalman       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	thread_doer(t_thread *main)
{
	int	i;

	i = -1;
	while (++i < main->no_of_philosophers)
	{
		pthread_create(main->philosophers[i]->philosopher, NULL \
			, &work, (void *)main->philosophers[i]);
		main->philosophers[i]->time_since_eat = timestamp();
	}
	i = -1;
	if (dead(main))
		return;
	while (++i < main->no_of_philosophers)
	{
		pthread_join(*main->philosophers[i]->philosopher, NULL);
		pthread_mutex_destroy(main->forks[i]);
	}
	pthread_mutex_destroy(&main->id_lock);
}

int	main(int ac, char **av)
{
	bool		check_arg;
	t_thread	*main;

	main = create(av, check_arg);
	check_arg = checker(ac, av);
	thread_doer(main);
	return (1);
}

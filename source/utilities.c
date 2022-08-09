/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayalman <ayalman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 21:13:40 by ayalman           #+#    #+#             */
/*   Updated: 2022/08/09 22:04:16 by ayalman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

long	timestamp(void)
{
	struct timeval	time;
	long			i;

	gettimeofday(&time, NULL);
	i = ((int)time.tv_sec * 1000) + ((int)time.tv_usec / 1000);
	return (i);
}

time_t	time_diff(time_t past, time_t present)
{
	return (present - past);
}

// void	smart_sleep(int ms)
// {
// 	long	time;

// 	time = timestamp();
// 	usleep(ms * 920);
// 	while (timestamp() < ms + time)
// 		usleep(ms * 3);
// }

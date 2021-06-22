/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanykim <chanykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 16:29:20 by chanykim          #+#    #+#             */
/*   Updated: 2021/06/22 17:26:39 by chanykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

uint64_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

uint64_t	ft_msleep(int time)
{
	uint64_t		start;
	uint64_t		end;
	start = get_time();
	while ((get_time() - start) < (uint64_t)time)
		usleep(100);
	end = get_time();
	//printf("%llu\n" , end - start);
	return (end - start);
}
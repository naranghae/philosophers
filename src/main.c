/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanykim <chanykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 14:26:08 by chanykim          #+#    #+#             */
/*   Updated: 2021/06/22 17:38:24 by chanykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*dining(void *philo)
{
	t_philo			*philos;
	static uint64_t	delay_time;

	philos = (t_philo *)philo;

	pthread_mutex_lock(&philos->mutex);
	printf("%d: lock\n", philos->pos);
	delay_time += ft_msleep(philos->state->tteat);
	printf("%llu ms : thread_end\n", delay_time);
	pthread_mutex_unlock(&philos->mutex);
	printf("%d: unlock\n", philos->pos);
	return (philo);
}

// 죽을 시간이 잘 시간보다 길면 안된다. 왜냐, 죽었는데 어떻게 자?
// 먹기 시작할 때부터 죽을 시간을 체크한다.
int			main(int arg, char **argv) // argv: [1]철학자 수 [2]죽을 시간 [3]먹을 시간 [4]잘 시간 [5]모든 철학자가 먹어야하는 횟수
{
	t_pstate		state;
	int				i;
	void			*ret;

	i = -1;
	if (first_error(arg, argv))
		return (0);
	if (init_state(&state, arg, argv) != 0)
		return (0);
	printf("%d, %d, %d, %d, %d\n", state.nophilo, state.ttdie, state.tteat, state.ttsleep, state.musteat);
	while (++i < state.nophilo)
	{
		if (pthread_create(&state.philos[i].id, NULL, dining, (void *)&state.philos[i]) != 0)
			return (error(THREAD_ERROR));
		printf("waiting\n");
		pthread_join(state.philos[i].id, &ret);
		pthread_mutex_destroy(&state.philos[i].mutex);
		printf("main_end\n");
	}
	return (0);
}
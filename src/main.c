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

void	*monitor(void *philo)
{
	t_philo			*philos;
	pthread_t		tid;
	philos = (t_philo *)philo;
	tid = pthread_self();
	printf("monitor: thread_id[%d]: %ld\n",philos->pos ,tid);
	printf("monitor: philo_id[%d]: %ld\n",philos->pos ,philos->id);
	sleep(4);
	return ((void*)0);
}

void	*dining(void *philo)
{
	t_philo			*philos;
	pthread_t		tid;
	philos = (t_philo *)philo;
	philos->last_eat = get_time();
	if (pthread_create(&tid, NULL, monitor, (void *)&philo))
		return ((void *)1);
	
	return ((void*)0);
}

// 죽을 시간이 잘 시간보다 길면 안된다. 왜냐, 죽었는데 어떻게 자?
// 먹기 시작할 때부터 죽을 시간을 체크한다.
int			main(int arg, char **argv) // argv: [1]철학자 수 [2]죽을 시간 [3]먹을 시간 [4]잘 시간 [5]모든 철학자가 먹어야하는 횟수
{
	t_pstate		state;
	//pthread_t 		monitor;
	int				i;

	i = -1;
	if (first_error(arg, argv))
		return (0);
	if (init_state(&state, arg, argv))
		return (0);
	printf("%d, %lld, %lld, %lld, %d\n", state.nophilo, state.ttdie, state.tteat, state.ttsleep, state.musteat);
	state.start_time = get_time();
	while (++i < state.nophilo)
	{
		if (pthread_create(&state.philos[i].id, NULL, dining, (void *)&state.philos[i]))
			return (error(THREAD_ERROR, &state));
	}
	i = -1;
	while (++i < state.nophilo)
			pthread_join(state.philos[i].id, NULL);
	free_philo(&state);
	//for(;;){}
	
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanykim <chanykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 14:26:08 by chanykim          #+#    #+#             */
/*   Updated: 2021/06/24 21:03:15 by chanykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor(void *state)
{
	t_pstate			*states;
	states = (t_pstate *)state;


	//if (states->philos[] == states->musteat)

	return ((void*)0);
}

void	*dining(void *philo)
{
	t_philo			*philos;
	pthread_t		tid;

	philos = (t_philo *)philo;

	pthread_create(&tid, NULL, monitor, (void *)&philos->state);
	pthread_detach(tid);
	while (1)
	{
		pick_fork(philos);
		eating(philos);
		return_fork(philos);
	}
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
		pthread_create(&state.philos[i].id, NULL, dining, (void *)&state.philos[i]);
		pthread_detach(state.philos[i].id);
	}
	i = -1;
	while (++i < state.nophilo)
			pthread_join(state.philos[i].id, NULL);
	free_philo(&state);
	//for(;;){}

	return (0);
}
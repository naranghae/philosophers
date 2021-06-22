/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanykim <chanykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 17:33:06 by chanykim          #+#    #+#             */
/*   Updated: 2021/06/22 17:32:08 by chanykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void		info_state(t_pstate *state, int arg, char **argv)
{
	state->nophilo = ft_atoi(argv[1]);
	state->ttdie = ft_atoi(argv[2]);
	state->tteat =ft_atoi(argv[3]);
	state->ttsleep = ft_atoi(argv[4]);
	if (arg == 6)
		state->musteat = ft_atoi(argv[5]);
	else
		state->musteat = 0;
	state->philos = NULL;
}

void		init_mutex(t_pstate *state)
{
	int		i;

	i = -1;
	while (++i < state->nophilo)
		pthread_mutex_init(&state->m_forks[i], NULL);
}

int			init_state(t_pstate *state, int arg, char **argv)
{
	info_state(state, arg, argv);
	if (state->nophilo < 1)
		return (error(NO_PHILO));
	if (!(state->philos = malloc(sizeof(*state->philos) * state->nophilo)))
		return (error(MALLOC_ERROR));
	if (!(state->m_forks = (pthread_mutex_t *)malloc(sizeof(*state->m_forks) *
			state->nophilo)))
		return (error(MALLOC_ERROR));
	init_mutex(state);
	init_philo(state);
	return (0);
}

void		init_philo(t_pstate *state)
{
	int		i;

	i = -1;
	while (++i < state->nophilo)
	{
		state->philos[i].pos = i;
		state->philos[i].eat_cnt = 0;
		state->philos[i].l_fork = i;
		state->philos[i].state = state;
		state->philos[i].r_fork = (i + 1) % (state->nophilo);
		pthread_mutex_init(&state->philos[i].mutex, NULL);
		pthread_mutex_init(&state->philos[i].m_eat, NULL);
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanykim <chanykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 17:33:06 by chanykim          #+#    #+#             */
/*   Updated: 2021/06/24 20:20:05 by chanykim         ###   ########.fr       */
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

int			init_state(t_pstate *state, int arg, char **argv)
{
	info_state(state, arg, argv);
	if (state->nophilo < 1)
		return (error(NO_PHILO, state));
	if (!(state->philos = malloc(sizeof(*state->philos) * state->nophilo)))
		return (error(MALLOC_ERROR, state));
	if (!(state->m_forks = (pthread_mutex_t *)malloc(sizeof(*state->m_forks) *
			state->nophilo)))
		return (error(MALLOC_ERROR, state));
	if (init_philo(state))
		return (error(MUTEX_ERROR, state));
	return (0);
}

int			init_philo(t_pstate *state)
{
	int		i;

	i = -1;
	while (++i < state->nophilo)
	{
		state->philos[i].pos = i;
		state->philos[i].eat_cnt = 0;
		state->philos[i].l_fork = i;
		state->philos[i].r_fork = (i + 1) % (state->nophilo);
		state->philos[i].state = state;
		if (pthread_mutex_init(&state->philos[i].m_eating, NULL))
			return (1);
		if (pthread_mutex_init(&state->m_forks[i], NULL))
			return (1);
	}
	if (pthread_mutex_init(&state->message, NULL))
		return (1);
	return (0);
}
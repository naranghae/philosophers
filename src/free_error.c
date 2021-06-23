/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanykim <chanykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 16:55:27 by chanykim          #+#    #+#             */
/*   Updated: 2021/06/22 12:44:50 by chanykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		first_error(int arg, char **argv)
{
	if (is_digit(argv) || (arg < 5 || arg > 6))
	{
		write(1, "argument_error\n", 15);
		return (1);
	}
	return (0);
}

int		error(int error, t_pstate *state)
{
	if (error == THREAD_ERROR)
		write(1, "Thread_create_error.\n", 21);
	else if (error == MALLOC_ERROR)
		write(1, "malloc_error\n", 13);
	else if (error == NO_PHILO)
		write(1, "Include at least 1 philosopher.\n", 32);
	else if (error == MUTEX_ERROR)
		write(1, "mutex_error\n", 12);
	if (error > 0)
	{
		free_philo(state);
		return (1);
	}
	return (0);
}

void		free_philo(t_pstate *state)
{
	int		i;

	i = -1;
	if (state != NULL)
	{
		pthread_mutex_destroy(&state->message);
		if (state->philos)
		{
			while (++i < state->nophilo)
				pthread_mutex_destroy(&state->philos[i].m_eating);
			free(state->philos);
			state->philos = NULL;
		}
		if (state->m_forks)
		{
			i = -1;
			while (++i < state->nophilo)
				pthread_mutex_destroy(&state->m_forks[i]);
			free(state->m_forks);
			state->m_forks = NULL;
		}
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_forks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 17:33:06 by chanykim          #+#    #+#             */
/*   Updated: 2021/06/23 12:57:21 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void		eating(t_philo *philo)
{

	pthread_mutex_lock(&philo->m_eating);
	philo->eat_time = get_time();
	ft_msleep(philo->state->tteat);
	philo->eat_cnt++;
	pthread_mutex_unlock(&philo->m_eating);
}

void		pick_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->state->m_forks[philo->l_fork]);
	pthread_mutex_lock(&philo->state->m_forks[philo->r_fork]);
}


void		return_fork(t_philo *philo)
{
	pthread_mutex_unlock(&philo->state->m_forks[philo->r_fork]);
	pthread_mutex_unlock(&philo->state->m_forks[philo->l_fork]);
}
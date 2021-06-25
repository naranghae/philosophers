/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_forks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanykim <chanykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 17:33:06 by chanykim          #+#    #+#             */
/*   Updated: 2021/06/24 20:51:47 by chanykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void		eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->m_eating);
	philo->last_eat = get_time();
	philo->eat_time = 1;
	//먹었다.
	ft_msleep(philo->info->tteat);
	philo->eat_cnt++;
	pthread_mutex_unlock(&philo->m_eating);
	philo->eat_time = 0;
}

void		pick_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->m_forks[philo->l_fork]);
	//들었다.
	pthread_mutex_lock(&philo->info->m_forks[philo->r_fork]);
	//들었다.
}

void		return_fork(t_philo *philo)
{
	pthread_mutex_unlock(&philo->info->m_forks[philo->r_fork]);
	pthread_mutex_unlock(&philo->info->m_forks[philo->l_fork]);
	//sleep
	ft_msleep(philo->info->ttsleep);
}
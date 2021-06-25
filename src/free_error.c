/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanykim <chanykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 16:55:27 by chanykim          #+#    #+#             */
/*   Updated: 2021/06/24 20:17:30 by chanykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		first_error(int arg, char **argv)
{
	if (is_digit(argv) || (arg < 5 || arg > 6))
	{
		printf("argument_error\n");
		return (1);
	}
	return (0);
}

int		error(int error, t_info *info)
{
	if (error == MALLOC_ERROR)
	{
		printf("malloc_error\n");
		return (malloc_free(info));
	}
	else if (error == NO_PHILO)
	{
		printf("Include at least 2 philosopher.\n");
		return (1);
	}
	else if (error == MUTEX_ERROR)
	{
		printf("mutex_error\n");
		return (mutex_destroy(info));
	}
	return (1);
}

int		mutex_destroy(t_info *info)
{
	int		i;

	i = -1;
	if (info != NULL)
	{
		if (info->philos)
		{
			while (++i < info->nophilo)
				pthread_mutex_destroy(&info->philos[i].m_eating);
		}
		if (info->m_forks)
		{
			i = -1;
			while (++i < info->nophilo)
				pthread_mutex_destroy(&info->m_forks[i]);
		}
		if (info->philos && info->m_forks)
			pthread_mutex_destroy(&info->message);
	}
	return (1);
}

int		malloc_free(t_info *info)
{
	if (info != NULL)
	{
		if (info->philos)
		{
			free(info->philos);
			info->philos = NULL;
		}
		if (info->m_forks)
		{
			free(info->m_forks);
			info->m_forks = NULL;
		}
	}
	return (1);
}


void	free_philo(t_info *info)
{
	malloc_free(info);
	mutex_destroy(info);
}
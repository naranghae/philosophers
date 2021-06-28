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

void		info_state(t_info *info, int arg, char **argv)
{
	info->nophilo = ft_atoi(argv[1]);
	info->ttdie = ft_atoi(argv[2]);
	info->tteat =ft_atoi(argv[3]);
	info->ttsleep = ft_atoi(argv[4]);
	if (arg == 6)
		info->musteat = ft_atoi(argv[5]);
	else
		info->musteat = 0;
	info->finish_eat = 0;
	info->quit = 0;
	info->philos = NULL;
	info->m_forks = NULL;
}

int			init_state(t_info *info, int arg, char **argv)
{
	info_state(info, arg, argv);
	if (info->nophilo <= 1)
		return (error(NO_PHILO, info));
	if (!(info->philos = malloc(sizeof(*info->philos) * info->nophilo)))
		return (error(MALLOC_ERROR, info));
	if (!(info->m_forks = malloc(sizeof(pthread_mutex_t) *
			info->nophilo)))
		return (error(MALLOC_ERROR, info));
	if (init_philo(info))
		return (error(MUTEX_ERROR, info));
	return (0);
}

int			init_philo(t_info *info)
{
	int		i;

	i = -1;
	while (++i < info->nophilo)
	{
		info->philos[i].pos = i + 1;
		info->philos[i].eat_cnt = 0;
		info->philos[i].eat_time = 0;
		info->philos[i].l_fork = i;
		info->philos[i].r_fork = (i + 1) % (info->nophilo);
		info->philos[i].info = info;
		info->philos[i].must_eat_flag = 0;
		if (pthread_mutex_init(&info->philos[i].m_eating, NULL))
			return (1);
		if (pthread_mutex_init(&info->m_forks[i], NULL))
			return (1);
	}
	if (pthread_mutex_init(&info->message, NULL))
		return (1);
	return (0);
}
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

int		limit_eat(void *philo)
{
	t_philo			*philos;

	philos = (t_philo *)philo;
	//printf("pos: %d, eat_cnt: %d\n", philos->pos, philos->eat_cnt);
	if (philos->eat_cnt == philos->info->musteat)
		philos->must_eat_flag = 1;
	if (philos->eat_cnt >= philos->info->musteat)
		philos->info->finish_eat++;
	if (philos->info->finish_eat == philos->info->nophilo)
	{
		//printf("%d\n", philos->pos);
		timestamp(philo, EAT_FINISHED);
		return (1);
	}
	return (0);
}

void	*monitor(void *philo)
{
	t_philo			*philos;

	philos = (t_philo *)philo;
	while (!philos->info->quit)
	{
		if (!philos->eat_time && !philos->info->quit)
		{
			if (get_time() - philos->last_eat > philos->info->ttdie)
			{
				timestamp(philos, DIE);
				return (NULL);
			}
		}
		ft_msleep(1);
	}
	return (NULL);
}

void	*dining(void *philo)
{
	t_philo			*philos;

	philos = (t_philo *)philo;
	//philos->last_eat = get_time();
	//printf("diing: lld\n", philos->last_eat);
	//printf("number: %d\n", philos->pos);
	while (!philos->must_eat_flag)
	{
		pick_fork(philos);
		eating(philos);
		return_fork(philos);
		if ((philos->info->musteat > 0) && limit_eat(philos))
			break ;
		sleep_philo(philos);
	}
	return (NULL);
}

// 죽을 시간이 잘 시간보다 길면 안된다. 왜냐, 죽었는데 어떻게 자?
// 먹기 시작할 때부터 죽을 시간을 체크한다.
int			main(int arg, char **argv) // argv: [1]철학자 수 [2]죽을 시간 [3]먹을 시간 [4]잘 시간 [5]모든 철학자가 먹어야하는 횟수
{
	t_info		info;
	int			i;
	pthread_t	tid;

	i = -1;
	if (first_error(arg, argv))
		return (0);
	if (init_state(&info, arg, argv))
		return (0);
	printf("%d, %lld, %lld, %lld, %d\n", info.nophilo, info.ttdie, info.tteat, info.ttsleep, info.musteat);
	info.start_time = get_time();
	while (++i < info.nophilo)
	{
		info.philos[i].last_eat = get_time();
		pthread_create(&tid, NULL, dining, (void *)&info.philos[i]);
		pthread_detach(tid);
		pthread_create(&info.philos[i].tid, NULL, monitor, (void *)&info.philos[i]);
		ft_msleep(1);
	}
	i = -1;
	while (++i < info.nophilo)
		pthread_join(info.philos[i].tid, NULL);
	free_philo(&info);
	//for(;;){}

	return (0);
}
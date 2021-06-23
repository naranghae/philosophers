/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanykim <chanykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 14:34:41 by chanykim          #+#    #+#             */
/*   Updated: 2021/06/22 17:21:25 by chanykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>
# include <stdlib.h>
# define MALLOC_ERROR	1
# define NO_PHILO		2
# define THREAD_ERROR	3
# define MUTEX_ERROR	4

typedef unsigned long long	uint64_t;

typedef struct			s_philo
{
	pthread_t			id;
	int					pos;
	int					r_fork;
	int					l_fork;
	int					eat_cnt;
	int					eat_time;
	uint64_t			last_eat;
	pthread_mutex_t		m_eating;
	struct s_pstate		*state;
}						t_philo;

typedef struct			s_pstate
{
	int					nophilo;
	uint64_t			ttdie;
	uint64_t			tteat;
	uint64_t			ttsleep;
	int					musteat;
	uint64_t			start_time;
	uint64_t			time_pass;
	t_philo				*philos;
	pthread_mutex_t		*m_forks;
	pthread_mutex_t		message;
}						t_pstate;

int						first_error(int arg, char **argv);
int						init_state(t_pstate *state, int arg, char **argv);
int						init_philo(t_pstate *state);
int						ft_atoi(char *str);
int						is_digit(char **str);
int						error(int error, t_pstate *state);
uint64_t				get_time(void);
void					ft_msleep(uint64_t time);
void					free_philo(t_pstate *state);
void					pick_fork(t_philo *philo);
void					return_fork(t_philo *philo);
void					eating(t_philo *philo);
#endif
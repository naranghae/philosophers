/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanykim <chanykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 14:34:41 by chanykim          #+#    #+#             */
/*   Updated: 2021/06/24 20:10:52 by chanykim         ###   ########.fr       */
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
# define MUTEX_ERROR	3
# define PICKFORK		0
# define EATING			1
# define SLEEPING		2
# define THINKING		3
# define DIE			4
# define EAT_FINISHED	5

typedef unsigned long long	uint64_t;

typedef struct			s_philo
{
	pthread_t			tid;
	int					pos;
	int					r_fork;
	int					l_fork;
	int					eat_cnt;
	int					eat_time;
	int					must_eat_flag;
	uint64_t			last_eat;
	pthread_mutex_t		m_eating;
	struct s_info		*info;
}						t_philo;

typedef struct			s_info
{
	int					nophilo;
	uint64_t			ttdie;
	uint64_t			tteat;
	uint64_t			ttsleep;
	int					musteat;
	int					finish_eat;
	int					quit;
	uint64_t			start_time;
	t_philo				*philos;
	pthread_mutex_t		*m_forks;
	pthread_mutex_t		message;
}						t_info;

int						first_error(int arg, char **argv);
int						init_state(t_info *info, int arg, char **argv);
int						init_philo(t_info *info);
int						ft_atoi(char *str);
int						is_digit(char **str);
int						error(int error, t_info *info);
uint64_t				get_time(void);
void					ft_msleep(uint64_t time);
void					free_philo(t_info *info);
void					pick_fork(t_philo *philo);
void					return_fork(t_philo *philo);
void					eating(t_philo *philo);
int						mutex_destroy(t_info *info);
int						malloc_free(t_info *info);
void					sleep_philo(t_philo *philo);
void					timestamp(t_philo *philo, int type);
#endif
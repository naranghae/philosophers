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

typedef struct			s_philo
{
	pthread_t			id;
	int					pos;
	int					r_fork;
	int					l_fork;
	int					eat_cnt;
	pthread_mutex_t		m_eat;
	pthread_mutex_t		mutex;
	struct s_pstate		*state;
}						t_philo;

typedef struct			s_pstate
{
	int					nophilo;
	int					ttdie;
	int					tteat;
	int					ttsleep;
	int					musteat;
	t_philo				*philos;
	pthread_mutex_t		*m_forks;
}						t_pstate;

int						first_error(int arg, char **argv);
int						init_state(t_pstate *state, int arg, char **argv);
void					init_philo(t_pstate *state);
int						ft_atoi(char *str);
int						is_digit(char **str);
int						error(int error);
uint64_t				get_time(void);
uint64_t				ft_msleep(int time);
#endif
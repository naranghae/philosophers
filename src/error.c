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

int		error(int error)
{
	if (error == MALLOC_ERROR)
	{
		write(1, "malloc_error\n", 13);
		return (1);
	}
	if (error == NO_PHILO)
	{
		write(1, "Include at least 1 philosopher.\n", 32);
		return (2);
	}
	if (error == THREAD_ERROR)
	{
		write(1, "Thread_create_error.\n", 21);
		return (0);
	}
	return (0);
}
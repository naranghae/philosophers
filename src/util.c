/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanykim <chanykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 20:17:55 by chanykim          #+#    #+#             */
/*   Updated: 2021/06/21 20:29:17 by chanykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		ft_atoi(char *str)
{
	unsigned long long		sol;
	int						i;

	i = 0;
	sol = 0;
	while (str[i] != '\0')
	{
		if (str[i] >= '0' && str[i] <= '9')
			sol = sol * 10 + str[i] - '0';
		i++;
	}
	return (sol);
}

int		is_digit(char **str)
{
	int		i;
	int		j;

	i = 0;
	while (str[++i] != NULL)
	{
		j = 0;
		while (str[i][j] != '\0')
		{
			if (str[i][j] >= '0' && str[i][j] <= '9')
				j++;
			else
				return (1);
		}
	}
	return (0);
}

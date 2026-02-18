/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadaniel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:27:11 by sadaniel          #+#    #+#             */
/*   Updated: 2026/02/12 12:27:19 by sadaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosophers.h"

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(int sleep)
{
	long long	start;

	start = get_time();
	while (get_time() - start < sleep)
	{
		if (get_time() - start > 100)
			usleep(100);
		else
			usleep(1);
	}
}

long	ft_atol(char *str)
{
	long	result;
	int	i;

	result = 0;
	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result *= 10;
		result += str[i] - '0';
		i++;
	}
	if (result > 2147483647 || result < -2147483648)
		return (-1);
	return (result);
}

int	check_args(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (1);
			j++;
		}
		i++;
	}
	if (i != 5 && i != 6)
		return (1);
	return (0);
}

int	check_data_values(t_data *data)
{
	if (data->time_to_die < 0 || data->time_to_eat < 0
		|| data->time_to_sleep < 0 || data->nb_philo == 0
		|| data->nb_philo > 200)
	{
		return (1);
	}
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadaniel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:26:44 by sadaniel          #+#    #+#             */
/*   Updated: 2026/02/12 12:26:48 by sadaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosophers.h"

void	free_philo_array(t_thread **philo_array)
{
	int	i;

	i = 0;
	if (philo_array)
	{
		while (philo_array[i])
		{
			free(philo_array[i]);
			i++;
		}
		free(philo_array);
	}
}

void	free_fork_array(t_fork **fork_array)
{
	int	i;

	i = 0;
	if (fork_array)
	{
		while (fork_array[i])
		{
			pthread_mutex_destroy(&fork_array[i]->fork_mutex);
			free(fork_array[i]);
			i++;
		}
		free(fork_array);
	}
}

void	free_data(t_data *data)
{
	if (data)
	{
		pthread_mutex_destroy(&data->print_mutex);
		free(data);
	}
}

void	free_monitor(t_monitor *monitor)
{
	if (monitor)
		free(monitor);
}

void	free_all(t_thread **philo_array, t_fork **fork_array, \
	t_data *data, t_monitor *monitor)
{
	free_philo_array(philo_array);
	free_fork_array(fork_array);
	free_data(data);
	free_monitor(monitor);
}

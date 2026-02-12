/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_thread.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadaniel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:26:59 by sadaniel          #+#    #+#             */
/*   Updated: 2026/02/12 12:27:02 by sadaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosophers.h"

int	check_meals(t_thread **philo_array)
{
	int	i;

	i = 0;
	while (philo_array[i]->meals_left == 0)
	{
		if (i + 1 == philo_array[i]->data->nb_philo)
			return (1);
		i++;
	}
	return (0);
}

void	death_message(t_monitor *monitor, int id)
{
	pthread_mutex_lock(&monitor->data->print_mutex);
	printf("%ld %d died\n", get_time() - monitor->data->start_time, id);
	pthread_mutex_unlock(&monitor->data->print_mutex);
}

void	*monitor_routine(void *args)
{
	t_monitor	*monitor;
	int			i;

	monitor = (t_monitor *)args;
	while (monitor->data->has_a_philo_died == 0)
	{
		i = 0;
		if (check_meals(monitor->philo_array) == 1)
			monitor->data->has_a_philo_died = 1;
		while (monitor->philo_array[i] && monitor->data->has_a_philo_died == 0)
		{
			if (get_time() - monitor->philo_array[i]->last_meal
				>= monitor->data->time_to_die)
			{
				monitor->data->has_a_philo_died = 1;
				death_message(monitor, monitor->philo_array[i]->id);
			}
			i++;
		}
		ft_usleep(10);
	}
	return (NULL);
}

t_monitor	*init_monitor(t_monitor *monitor, \
	t_data *data, t_thread **philo_array)
{
	monitor = malloc(sizeof(t_monitor));
	if (!monitor)
		return (NULL);
	monitor->data = data;
	monitor->philo_array = philo_array;
	pthread_create(&monitor->monitor_thread, NULL, monitor_routine, monitor);
	return (monitor);
}

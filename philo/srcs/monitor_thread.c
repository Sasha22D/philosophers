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
#include "../include/philosophers.h"

void	*monitor_routine(void *args)
{
	t_monitor	*monitor;
	long		last_meal;
	int			i;

	monitor = (t_monitor *)args;
	while (1)
	{
		pthread_mutex_lock(&monitor->data->start_mutex);
		if (monitor->data->initialized_count == monitor->data->nb_philo)
		{
			pthread_mutex_unlock(&monitor->data->start_mutex);
			ft_usleep(100);
			break ;
		}
		pthread_mutex_unlock(&monitor->data->start_mutex);
		usleep(1);
	}
	while (check_death(monitor->philo_array[0]) == 0)
	{
		i = 0;
		if (check_meals(monitor->philo_array) == 1)
			set_death(monitor);
		while (monitor->philo_array[i] && monitor->data->has_a_philo_died == 0)
		{
			pthread_mutex_lock(&monitor->philo_array[i]->meal_mutex);
			last_meal = get_time() - monitor->philo_array[i]->last_meal;
			pthread_mutex_unlock(&monitor->philo_array[i]->meal_mutex);
			if (last_meal >= monitor->data->time_to_die)
			{
				set_death(monitor);
				death_message(monitor, monitor->philo_array[i]->id);
			}
			i++;
		}
		ft_usleep(1);
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

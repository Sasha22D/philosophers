/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spinlocks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadaniel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 11:27:50 by sadaniel          #+#    #+#             */
/*   Updated: 2026/03/31 11:27:55 by sadaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosophers.h"

void	philo_spinlock(t_thread *philo)
{
	pthread_mutex_lock(&philo->data->start_mutex);
	philo->data->ready_count++;
	if (philo->data->ready_count == philo->data->nb_philo)
	{
		philo->data->start_time = get_time();
		philo->data->all_ready = 1;
	}
	pthread_mutex_unlock(&philo->data->start_mutex);
	while (1)
	{
		pthread_mutex_lock(&philo->data->start_mutex);
		if (philo->data->all_ready == 1)
		{
			pthread_mutex_unlock(&philo->data->start_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->data->start_mutex);
		usleep(1);
	}
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = philo->data->start_time;
	pthread_mutex_unlock(&philo->meal_mutex);
	pthread_mutex_lock(&philo->data->start_mutex);
	philo->data->initialized_count++;
	pthread_mutex_unlock(&philo->data->start_mutex);
}

void	monitor_spinlock(t_monitor *monitor)
{
	while (1)
	{
		pthread_mutex_lock(&monitor->data->start_mutex);
		if (monitor->data->initialized_count == monitor->data->nb_philo)
		{
			pthread_mutex_unlock(&monitor->data->start_mutex);
			ft_usleep(60);
			break ;
		}
		pthread_mutex_unlock(&monitor->data->start_mutex);
		usleep(1);
	}
}

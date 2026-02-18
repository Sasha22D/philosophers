/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadaniel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 12:52:39 by sadaniel          #+#    #+#             */
/*   Updated: 2026/02/18 12:52:44 by sadaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/philosophers.h"

int	check_meals(t_thread **philo_array)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (philo_array[i])
	{
		pthread_mutex_lock(&philo_array[i]->meal_mutex);
		if (philo_array[i]->meals_left == 0)
			j++;
		pthread_mutex_unlock(&philo_array[i]->meal_mutex);
		if (j == philo_array[0]->data->nb_philo)
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

void	set_death(t_monitor *monitor)
{
	pthread_mutex_lock(&monitor->data->death_mutex);
	monitor->data->has_a_philo_died = 1;
	pthread_mutex_unlock(&monitor->data->death_mutex);
}

int	check_death(t_thread *philo)
{
	int	dead;

	dead = 0;
	pthread_mutex_lock(&philo->data->death_mutex);
	if (philo->data->has_a_philo_died == 1)
		dead = 1;
	pthread_mutex_unlock(&philo->data->death_mutex);
	return (dead);
}

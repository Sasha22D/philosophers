/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadaniel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 13:07:13 by sadaniel          #+#    #+#             */
/*   Updated: 2026/02/16 13:07:16 by sadaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosophers.h"

int	create_solo_pthread(t_thread **philo_array, int meals_left)
{
	int	thread_created;

	philo_array[0]->meals_left = meals_left;
	thread_created = pthread_create(&philo_array[0]->philo, NULL, \
			one_philo_routine, philo_array[0]);
	if (thread_created != 0)
		return (1);
	return (0);
}

int	create_meal_pthread(t_thread **philo_array)
{
	int	i;
	int	thread_created;

	i = 0;
	thread_created = 0;
	while (philo_array[i])
	{
		thread_created = pthread_create(&philo_array[i]->philo, NULL, \
			philo_routine_must_eat, philo_array[i]);
		if (thread_created != 0)
			return (1);
		i++;
	}
	return (0);
}

int	create_no_meal_pthread(t_thread **philo_array)
{
	int	i;
	int	thread_created;

	i = 0;
	thread_created = 0;
	while (philo_array[i])
	{
		thread_created = pthread_create(&philo_array[i]->philo, NULL, \
			philo_routine, philo_array[i]);
		if (thread_created != 0)
			return (1);
		i++;
	}
	return (0);
}

int	create_pthreads(t_thread **philo_array, int meals_left, int nb_philo)
{
	if (nb_philo == 1 && meals_left != 0)
		return (create_solo_pthread(philo_array, meals_left) != 0);
	else if (meals_left != 0 && meals_left != -1)
		return (create_meal_pthread(philo_array));
	else if (meals_left == -1)
		return (create_no_meal_pthread(philo_array));
	return (0);
}

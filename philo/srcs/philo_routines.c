/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routines.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadaniel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:27:03 by sadaniel          #+#    #+#             */
/*   Updated: 2026/02/12 12:27:06 by sadaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/philosophers.h"

void	odds_think(t_thread *philo)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%ld %d is thinking\n", get_time() - \
	philo->data->start_time, philo->id);
	pthread_mutex_unlock(&philo->data->print_mutex);
	ft_usleep(philo->data->time_to_eat);
}

void	drop_forks(t_thread *philo)
{
	pthread_mutex_unlock(&philo->fork_left->fork_mutex);
	pthread_mutex_unlock(&philo->fork_right->fork_mutex);
}

void	*philo_routine(void *args)
{
	t_thread	*philo;

	philo = (t_thread *)args;
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

	if (philo->id % 2 != 0)
		odds_think(philo);
	while (check_death(philo) == 0)
	{
		if (philo->id % 2 != 0)
		{
			take_fork_right(philo);
			take_fork_left(philo);
		}
		else
		{
			take_fork_left(philo);
			take_fork_right(philo);
		}
		eat(philo);
		drop_forks(philo);
		ft_sleep(philo);
		think(philo);
	}
	return (NULL);
}

void	*philo_routine_must_eat(void *args)
{
	t_thread	*philo;

	philo = (t_thread *)args;
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

	if (philo->id % 2 != 0)
		odds_think(philo);
	while (check_death(philo) == 0 && philo->meals_left > 0)
	{
		if (philo->id % 2 != 0)
		{
			take_fork_right(philo);
			take_fork_left(philo);
		}
		else
		{
			take_fork_left(philo);
			take_fork_right(philo);
		}
		eat(philo);
		drop_forks(philo);
		ft_sleep(philo);
		think(philo);
	}
	return (NULL);
}

void	*one_philo_routine(void *args)
{
	t_thread	*philo;

	philo = (t_thread *)args;
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("0 1 has taken a fork\n");
	pthread_mutex_unlock(&philo->data->print_mutex);
	return (NULL);
}

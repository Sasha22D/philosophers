/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_actions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadaniel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:27:07 by sadaniel          #+#    #+#             */
/*   Updated: 2026/02/12 12:27:10 by sadaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/philosophers.h"

void	take_fork_right(t_thread *philo)
{
	long	now;

	now = get_time();
	pthread_mutex_lock(&philo->fork_right->fork_mutex);
	pthread_mutex_lock(&philo->data->print_mutex);
	if (check_death(philo) == 1)
	{
		pthread_mutex_unlock(&philo->fork_right->fork_mutex);
		pthread_mutex_unlock(&philo->data->print_mutex);
		return ;
	}
	printf("%ld %d has taken a fork\n", now - philo->data->start_time, \
		philo->id);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void	take_fork_left(t_thread *philo)
{
	long	now;

	now = get_time();
	pthread_mutex_lock(&philo->fork_left->fork_mutex);
	pthread_mutex_lock(&philo->data->print_mutex);
	if (check_death(philo) == 1)
	{
		pthread_mutex_unlock(&philo->fork_left->fork_mutex);
		pthread_mutex_unlock(&philo->data->print_mutex);
		return ;
	}
	printf("%ld %d has taken a fork\n", now - philo->data->start_time, \
		philo->id);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void	eat(t_thread *philo)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	if (check_death(philo) == 1)
	{
		pthread_mutex_unlock(&philo->data->print_mutex);
		return ;
	}
	printf("%ld %d is eating\n", get_time() - philo->data->start_time, \
		philo->id);
	pthread_mutex_unlock(&philo->data->print_mutex);
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = get_time();
	philo->meals_left--;
	pthread_mutex_unlock(&philo->meal_mutex);
}

void	ft_sleep(t_thread *philo)
{
	long	now;

	now = get_time();
	pthread_mutex_lock(&philo->data->print_mutex);
	if (check_death(philo) == 1)
	{
		pthread_mutex_unlock(&philo->data->print_mutex);
		return ;
	}
	printf("%ld %d is sleeping\n", now - philo->data->start_time, \
		philo->id);
	pthread_mutex_unlock(&philo->data->print_mutex);
	ft_usleep(philo->data->time_to_sleep);
}

void	think(t_thread *philo)
{
	long	now;

	now = get_time();
	pthread_mutex_lock(&philo->data->print_mutex);
	if (check_death(philo) == 1)
	{
		pthread_mutex_unlock(&philo->data->print_mutex);
		return ;
	}
	printf("%ld %d is thinking\n", now - philo->data->start_time, \
		philo->id);
	pthread_mutex_unlock(&philo->data->print_mutex);
	if (philo->data->nb_philo % 2 != 0)
		ft_usleep((philo->data->time_to_die - philo->data->time_to_eat - \
			philo->data->time_to_sleep) / 2);
}

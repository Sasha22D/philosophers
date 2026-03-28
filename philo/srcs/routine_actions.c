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

void	write_actions(int id, long long time, char *action)
{
	char	*id_string;
	char	*time_string;

	id_string = ft_lltoa(id);
	time_string = ft_lltoa(time);
	write(1, time_string, ft_strlen(time_string));
	write(1, " ", 1);
	write(1, id_string, ft_strlen(id_string));
	if (!ft_strcmp(action, "FLEFT"))
		write(1, " has taken a fork\n", 18);
	else if (!ft_strcmp(action, "FRIGHT"))
		write(1, " has taken a fork\n", 18);
	else if (!ft_strcmp(action, "EAT"))
		write(1, " is eating\n", 11);
	else if (!ft_strcmp(action, "SLEEP"))
		write(1, " is sleeping\n", 13);
	else if (!ft_strcmp(action, "THINK"))
		write(1, " is thinking\n", 13);
	else if (!ft_strcmp(action, "DIE"))
		write(1, "died\n", 5);
}

void	take_fork_right(t_thread *philo)
{
	long	now;

	pthread_mutex_lock(&philo->fork_right->fork_mutex);
	now = get_time() - philo->data->start_time;
	pthread_mutex_lock(&philo->data->print_mutex);
	if (check_death(philo) == 1)
	{
		pthread_mutex_unlock(&philo->fork_right->fork_mutex);
		pthread_mutex_unlock(&philo->data->print_mutex);
		return ;
	}
	write_actions(philo->id, now, "FLEFT");
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void	take_fork_left(t_thread *philo)
{
	long	now;

	pthread_mutex_lock(&philo->fork_left->fork_mutex);
	now = get_time() - philo->data->start_time;
	pthread_mutex_lock(&philo->data->print_mutex);
	if (check_death(philo) == 1)
	{
		pthread_mutex_unlock(&philo->fork_left->fork_mutex);
		pthread_mutex_unlock(&philo->data->print_mutex);
		return ;
	}
	write_actions(philo->id, now, "FRIGHT");
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void	eat(t_thread *philo)
{
	long long now;
	pthread_mutex_lock(&philo->data->print_mutex);
	now = get_time() - philo->data->start_time;
	if (check_death(philo) == 1)
	{
		pthread_mutex_unlock(&philo->data->print_mutex);
		return ;
	}
	write_actions(philo->id, now, "EAT");
	pthread_mutex_unlock(&philo->data->print_mutex);
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = get_time();
	philo->meals_left--;
	pthread_mutex_unlock(&philo->meal_mutex);
}

void	ft_sleep(t_thread *philo)
{
	long long	now;

	pthread_mutex_lock(&philo->data->print_mutex);
	now = get_time() - philo->data->start_time;
	if (check_death(philo) == 1)
	{
		pthread_mutex_unlock(&philo->data->print_mutex);
		return ;
	}
	write_actions(philo->id, now, "SLEEP");
	pthread_mutex_unlock(&philo->data->print_mutex);
	ft_usleep(philo->data->time_to_sleep);
}

void	think(t_thread *philo)
{
	long long	now;

	pthread_mutex_lock(&philo->data->print_mutex);
	now = get_time() - philo->data->start_time;
	if (check_death(philo) == 1)
	{
		pthread_mutex_unlock(&philo->data->print_mutex);
		return ;
	}
	write_actions(philo->id, now, "THINK");
	pthread_mutex_unlock(&philo->data->print_mutex);
	if (philo->data->nb_philo % 2 != 0)
		ft_usleep((philo->data->time_to_die - philo->data->time_to_eat - \
			philo->data->time_to_sleep) / 2);
}

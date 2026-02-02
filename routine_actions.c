#include "philosophers.h"

void	take_forks(t_thread *philo)
{
	if (philo->data->has_a_philo_died == 0)
	{
		pthread_mutex_lock(&philo->fork_left->fork_mutex);
		printf("%ld %d has taken a fork\n", philo->data->actual_time, philo->id);
		pthread_mutex_lock(&philo->fork_right->fork_mutex);
		printf("%ld %d has taken a fork\n", philo->data->actual_time, philo->id);
	}
}

void	drop_forks(t_thread *philo)
{
		pthread_mutex_unlock(&philo->fork_left->fork_mutex);
		pthread_mutex_unlock(&philo->fork_right->fork_mutex);
}

void	eat(t_thread *philo)
{
	if (philo->data->has_a_philo_died == 0)
	{
		printf("%ld %d is eating\n", philo->data->actual_time, philo->id);
		philo->last_meal = get_time();
		ft_usleep(philo->data->time_to_eat);
	}
}

void	ft_sleep(t_thread *philo)
{
	if (philo->data->has_a_philo_died == 0)
	{
		printf("%ld %d is sleeping\n", philo->data->actual_time, philo->id);
		ft_usleep(philo->data->time_to_sleep);
	}
}

void	think(t_thread *philo)
{
	if (philo->data->has_a_philo_died == 0)
	{
		printf("%ld %d is thinking\n", philo->data->actual_time, philo->id);
	}
}

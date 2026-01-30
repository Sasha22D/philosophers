#include "philosophers.h"

void	take_forks(t_thread *philo)
{
	if (philo->data->has_a_philo_died == 0)
	{
		pthread_mutex_lock(&philo->fork_left->fork_mutex);
		printf("%ld %d has taken a fork\n", philo->data->actual_time, philo->id);
		pthread_mutex_lock(&philo->fork_right->fork_mutex);
		if (philo->data->has_a_philo_died == 0)
		{
			printf("%ld %d has taken a fork\n", philo->data->actual_time, philo->id);
		}
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
		printf("%ld %d is thinking\n", philo->data->actual_time, philo->id);
}

void	*philo_routine(void *args)
{
	t_thread	*philo = (t_thread *)args;
	// long		now;

	if (philo->id % 2 != 0)
	{
		printf("0 %d is thinking\n", philo->id);
		ft_usleep(philo->data->time_to_eat);
	}
	while (philo->data->has_a_philo_died == 0)
	{
		take_forks(philo);
		eat(philo);
		drop_forks(philo);
		ft_sleep(philo);
		think(philo);
	}
	return (NULL);
}

void	*monitor_routine(void *args)
{
	t_monitor	*monitor = (t_monitor *)args;
	int	i;

	while (monitor->data->has_a_philo_died == 0)
	{
		i = 0;
		monitor->data->actual_time = get_time() - monitor->data->start_time;
		while (monitor->philo_array[i] && monitor->data->has_a_philo_died == 0)
		{
			if (get_time() - monitor->philo_array[i]->last_meal >= monitor->data->time_to_die)
			{
				monitor->data->has_a_philo_died = 1;
				printf("%ld %d died\n", monitor->data->actual_time, monitor->philo_array[i]->id);
			}
			i++;
		}
		// ft_usleep(100);
	}
	return (NULL);
}

void	init_monitor(t_monitor *monitor, t_data *data, t_thread **philo_array)
{
	monitor->data = data;
	monitor->philo_array = philo_array;
	pthread_create(&monitor->monitor_thread, NULL, monitor_routine, monitor);
}

int	main(int ac, char **av)
{
	(void)ac;
	t_thread	**philo_array;
	t_data		*data;
	t_fork		**fork_array;
	t_monitor	*monitor;
	int			count;
	int			i;

	data = malloc(sizeof(t_data));
	monitor = malloc(sizeof(t_monitor));

	i = 0;
	count = atoi(av[1]);
	init_data(data);
	philo_array = init_struct_array(count, data);
	fork_array = init_fork_array(count);
	assign_forks(fork_array, philo_array, count);
	create_pthread(philo_array);
	init_monitor(monitor, data, philo_array);
	
	pthread_join(monitor->monitor_thread, NULL);
	while (i < count)
	{
		pthread_join(philo_array[i]->philo, NULL);
		i++;
	}
}

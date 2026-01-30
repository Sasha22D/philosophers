#include "philosophers.h"

void	take_forks(t_thread *philo, long now)
{
	pthread_mutex_lock(&philo->fork_left->fork_mutex);
	printf("%ld %d has taken a fork\n", now - philo->data->start_time, philo->id);
	pthread_mutex_lock(&philo->fork_right->fork_mutex);
	printf("%ld %d has taken a fork\n", now - philo->data->start_time, philo->id);
}

void	drop_forks(t_thread *philo)
{
	long	now;

	now = get_time();
	pthread_mutex_unlock(&philo->fork_left->fork_mutex);
	// printf("%ld %d dropped left fork\n", now - philo->data->start_time, philo->id);
	pthread_mutex_unlock(&philo->fork_right->fork_mutex);
	// printf("%ld %d dropped right fork\n", now - philo->data->start_time, philo->id);
}

void	*philo_routine(void *args)
{
	t_thread	*philo = (t_thread *)args;
	long		now;

	if (philo->id % 2 != 0)
	{
		printf("0 %d is thinking\n", philo->id);
		ft_usleep(philo->data->time_to_eat);
	}
	while (philo->data->has_a_philo_died == 0)
	{
		now = get_time();
		// TAKE FORKS ()
		take_forks(philo, now);
		// EAT()
		printf("%ld %d is eating\n", now - philo->data->start_time, philo->id);
		philo->last_meal = now;
		ft_usleep(philo->data->time_to_eat);
		// DROP FORKS()
		drop_forks(philo);
		// SLEEP()
		now = get_time();
		printf("%ld %d is sleeping\n", now - philo->data->start_time, philo->id);
		ft_usleep(philo->data->time_to_sleep);
		// THINK()
		now = get_time();
		printf("%ld %d is thinking\n", now - philo->data->start_time, philo->id);
		// ft_usleep(1);
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
		while (monitor->philo_array[i] && monitor->data->has_a_philo_died == 0)
		{
			if (get_time() - monitor->philo_array[i]->last_meal >= monitor->data->time_to_die)
			{
				monitor->data->has_a_philo_died = 1;
				printf("%d has died\n", monitor->philo_array[i]->id);
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

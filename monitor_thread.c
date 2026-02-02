#include "philosophers.h"

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
				pthread_mutex_lock(&monitor->data->print_mutex);
				printf("%ld %d died\n", monitor->data->actual_time, monitor->philo_array[i]->id);
				// pthread_mutex_unlock(&monitor->data->print_mutex);
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

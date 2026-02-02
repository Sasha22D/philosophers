#include "philosophers.h"

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

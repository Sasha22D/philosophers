#include "philosophers.h"

int	main(int ac, char **av)
{
	t_thread	**philo_array;
	t_data		*data;
	t_fork		**fork_array;
	t_monitor	*monitor;
	int			count;
	int			i;
	(void)ac;

	i = 0;
	count = atoi(av[1]);
	monitor = malloc(sizeof(t_monitor));
	data = init_data(atoi(av[2]), atoi(av[3]), atoi(av[4]));
	if (ac == 6)
		philo_array = init_struct_array(data, count, atoi(av[5]));
	else
		philo_array = init_struct_array(data, count, -1);
	fork_array = init_fork_array(count);
	assign_forks(fork_array, philo_array, count);
	create_pthread(philo_array, philo_array[0]->meals_left);
	init_monitor(monitor, data, philo_array);

	pthread_join(monitor->monitor_thread, NULL);
	while (i < count)
	{
		pthread_join(philo_array[i]->philo, NULL);
		i++;
	}
}

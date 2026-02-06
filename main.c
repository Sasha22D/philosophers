#include "philosophers.h"

void	join_pthreads(t_thread **philo_array, t_monitor *monitor, int count)
{
	int	i;

	i = 0;
	pthread_join(monitor->monitor_thread, NULL);
	while (i < count)
	{
		pthread_join(philo_array[i]->philo, NULL);
		i++;
	}
}

int	init_philo(t_thread ***philo_array, t_fork ***fork_array, t_data *data)
{
	*philo_array = init_struct_array(data, data->nb_philo, data->meals);
	*fork_array = init_fork_array(data->nb_philo);
	if (!*philo_array || !*fork_array)
	{
		free_all(*philo_array, *fork_array, data, NULL);
		return (1);
	}
	assign_forks(*fork_array, *philo_array, data->nb_philo);
	create_pthread(*philo_array, data->meals);
	return (0);
}

int	main(int ac, char **av)
{
	t_thread	**philo_array;
	t_data		*data;
	t_fork		**fork_array;
	t_monitor	*monitor;
	int			count;

	philo_array = NULL;
	fork_array = NULL;
	monitor = NULL;
	if (check_args(av) == 1)
		return (0);
	count = ft_atoi(av[1]);
	data = init_data(ac, av);
	if (!data)
		return (1);
	if (init_philo(&philo_array, &fork_array, data) == 1)
		return (1);
	monitor = init_monitor(monitor, data, philo_array);
	if (!monitor)
		return (free_all(philo_array, fork_array, data, monitor), 1);
	join_pthreads(philo_array, monitor, count);
}

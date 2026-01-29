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
		ft_usleep(philo->data->time_to_eat);
	while (philo->data->has_a_philo_died == 0)
	{
		now = get_time();
		// TAKE FORKS ()
		take_forks(philo, now);
		// EAT()
		printf("%ld %d is eating\n", now - philo->data->start_time, philo->id);
		// DROP FORKS()
		drop_forks(philo);
		
		// SLEEP()
		ft_usleep(philo->data->time_to_sleep);
		
		// THINK()
		ft_usleep(200);
	}
	
	return (NULL);
}

int	main(int ac, char **av)
{
	(void)ac;
	t_thread	**philo_array;
	t_data		*data;
	t_fork		**fork_array;
	int			count;
	int			i;

	data = malloc(sizeof(t_data));

	i = 0;
	count = atoi(av[1]);
	init_data(data);
	philo_array = init_struct_array(count, data);
	fork_array = init_fork_array(count);
	assign_forks(fork_array, philo_array, count);
	create_pthread(philo_array);
	
	i = 0;
	while (i < count)
	{
		pthread_join(philo_array[i]->philo, NULL);
		i++;
	}
}

#include "philosophers.h"

t_data	*init_data(int time_to_die, int time_to_eat, int time_to_sleep)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->start_time = get_time();
	data->has_a_philo_died = 0;
	data->time_to_die = time_to_die;
	data->time_to_eat = time_to_eat;
	data->time_to_sleep = time_to_sleep;
	pthread_mutex_init(&data->print_mutex, NULL);
	return (data);
}

t_thread	**init_struct_array(t_data *data, int	count, int	meals_left)
{
	t_thread	**array;
	int			i;

	i = 0;
	array = malloc(sizeof(t_thread *) * count);
	if (!array)
		return (NULL);
	while (i < count)
	{
		array[i] = malloc(sizeof(t_thread));
		array[i]->id = i + 1;
		array[i]->data = data;
		array[i]->last_meal = data->start_time;
		array[i]->meals_left = meals_left;
		i++;
	}
	array[i] = NULL;
	return (array);
}

void	create_pthread(t_thread **philo_array, int meals_left)
{
	int	i;

	i = 0;
	if (meals_left != -1 && meals_left != 0)
	{
		while (philo_array[i])
		{
			pthread_create(&philo_array[i]->philo, NULL, philo_routine_must_eat, philo_array[i]);
			i++;
		}
	}
	else if (meals_left == -1)
	{
		while (philo_array[i])
		{
			pthread_create(&philo_array[i]->philo, NULL, philo_routine, philo_array[i]);
			i++;
		}
	}
}

t_fork	**init_fork_array(int count)
{
	t_fork	**array;
	int		i;

	i = 0;
	array = malloc(sizeof(t_fork *) * count);
	if (!array)
		return (NULL);
	while (i < count)
	{
		array[i] = malloc(sizeof(t_fork));
		array[i]->id = i + 1;
		pthread_mutex_init(&array[i]->fork_mutex, NULL);
		i++;
	}
	array[i] = NULL;
	return (array);
}

void	assign_forks(t_fork **fork_array, t_thread **philo_array, int count)
{
	int	i;

	i = 0;
	while (philo_array[i])
	{
		if (i == 0)
		{
			philo_array[i]->fork_left = fork_array[i];
			philo_array[i]->fork_right = fork_array[i + 1];
		}
		else if (i == count - 1)
		{
			philo_array[i]->fork_left = fork_array[i];
			philo_array[i]->fork_right = fork_array[0];
		}
		else
		{
			philo_array[i]->fork_left = fork_array[i];
			philo_array[i]->fork_right = fork_array[i + 1];
		}
		i++;
	}
}

#include "philosophers.h"

t_data	*init_data(int ac, char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->start_time = get_time();
	data->has_a_philo_died = 0;
	data->nb_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->meals = ft_atoi(av[5]);
	else
		data->meals = -1;
	pthread_mutex_init(&data->print_mutex, NULL);
	return (data);
}

t_thread	**init_struct_array(t_data *data, int count, int meals_left)
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
		if (!array[i])
		{
			while (--i >= 0)
				free(array[i]);
			free(array);
			return (NULL);
		}
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
		if (!array[i])
		{
			while (--i >= 0)
			{
				pthread_mutex_destroy(&array[i]->fork_mutex);
				free(array[i]);
			}
			free(array);
			return (NULL);
		}
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

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct s_fork
{
	int	id;
	pthread_mutex_t fork_mutex;
}				t_fork;

typedef struct s_thread
{
	int	id;
	pthread_t	philo;
	t_fork	*fork_left;
	t_fork	*fork_right;
}t_thread;

void	*philo_routine(void *args)
{
	t_thread	*thread = (t_thread *)args;
	printf("Philo %d prend sa fourchette de gauche\n", thread->id);
	return (NULL);
}

t_thread	**init_struct_array(int	count)
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
		pthread_create(&array[i]->philo, NULL, philo_routine, array[i]);
		i++;
	}
	return (array);
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

int	main()
{
	t_thread	**philo_array;
	t_fork		**fork_array;
	int			count;
	int			i;

	i = 0;
	count = 10;
	philo_array = init_struct_array(count);
	fork_array = init_fork_array(count);
	assign_forks(fork_array, philo_array, count);
	
	while (philo_array[i])
	{
		printf("Philo %d, fork_left id : %d, fork_right id : %d\n", philo_array[i]->id, philo_array[i]->fork_left->id, philo_array[i]->fork_right->id);
		i++;
	}
	
	
	
	// while (i < count)
	// {
	// 	pthread_join(philo_array[i]->philo, NULL);
	// 	i++;
	// }
}
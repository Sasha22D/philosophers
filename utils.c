#include "philosophers.h"

long	get_time()
{
	struct timeval tv;
	
	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(int sleep)
{
	long long	start;

	start = get_time();
	while (get_time() - start < sleep)
		usleep(1);
}
int ft_atoi(char *str)
{
    int result;
    int i;

    result = 0;
    i = 0;
    while (str[i] >= '0' && str[i] <= '9')
    {
        result *= 10;
        result += str[i] - '0';
        i++;
    }
    return (result);
}

int	check_args(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (1);
			j++;
		}
		i++;
	}
	if (i != 5 && i != 6)
		return (1);
	return (0);
}

void	free_all(t_thread **philo_array, t_fork **fork_array, t_data *data)
{
	int	i;

	if (philo_array)
	{
		i = 0;
		while (philo_array[i])
			free(philo_array[i++]);
		free(philo_array);
	}
	if (fork_array)
	{
		i = 0;
		while (fork_array[i])
		{
			pthread_mutex_destroy(&fork_array[i]->fork_mutex);
			free(philo_array[i++]);
		}
		free(fork_array);
	}
	if (data)
	{
		pthread_mutex_destroy(&data->print_mutex);
		free(data);
	}
}

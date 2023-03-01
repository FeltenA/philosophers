
#include "philo_bonus.h"
#include <unistd.h>
#include <stdlib.h>

void	philosopher(t_philo *philo);
int		philo_print(t_philo *philo, struct timeval time,
			const char *str);
int		destroy_all(t_data *data, int type, int n);
char	*ft_itoa(int n);

void	*check_eaten(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	i = -1;
	while (++i < data->nb_philo)
		sem_wait(data->eaten);
	sem_post(data->finish);
	return (0);
}

int	launch_philos(t_data *data)
{
	int				i;
	pthread_t		eaten;
	struct timeval	time;

	i = -1;
	gettimeofday(&time, 0);
	data->t_start = time.tv_sec * 1000 + time.tv_usec / 1000;
	if (data->n_eat > 0)
	{
		if (pthread_create(&eaten, 0, check_eaten, data))
			return (destroy_all(data, 2, data->nb_philo));
		pthread_detach(eaten);
	}
	while (++i < data->nb_philo)
	{
		data->philos[i].pid = fork();
		if (!data->philos[i].pid)
			philosopher(&data->philos[i]);
		else if (data->philos[i].pid < 0)
			return (destroy_all(data, 3, i));
	}
	return (1);
}

int	init_philo(t_data *data, int id)
{
	char	*name;

	name = ft_itoa(id);
	if (!name)
		return (0);
	sem_unlink(name);
	data->philos[id].check = sem_open(name, O_CREAT, 0600, 1);
	free(name);
	data->philos[id].id = id;
	data->philos[id].nb_eat = 0;
	data->philos[id].data = data;
	return (1);
}

int	init_data(t_data *data)
{
	int	i;

	sem_unlink("finish");
	sem_unlink("write");
	sem_unlink("forks");
	sem_unlink("eaten");
	data->finish = sem_open("finish", O_CREAT, 0600, 0);
	data->write = sem_open("write", O_CREAT, 0600, 1);
	data->forks = sem_open("forks", O_CREAT, 0600, data->nb_philo);
	data->eaten = sem_open("eaten", O_CREAT, 0600, 0);
	data->philos = malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->philos)
		return (destroy_all(data, 0, 0));
	i = -1;
	while (++i < data->nb_philo)
		if (!init_philo(data, i))
			return (destroy_all(data, 1, i));
	return (1);
}

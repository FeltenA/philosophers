
#include "philo.h"
#include <stdio.h>
#include <unistd.h>

int	check_time(t_philo *philo);

int	check_died(t_data *data)
{
	int	check;

	pthread_mutex_lock(&data->check);
	check = data->died;
	pthread_mutex_unlock(&data->check);
	return (check);
}

int	philo_print(t_philo *philo, struct timeval time, const char *str, int type)
{
	unsigned long long	timestamp;

	if (!type && check_died(philo->data))
		return (1);
	timestamp = time.tv_sec * 1000 + time.tv_usec / 1000;
	timestamp -= philo->data->t_start;
	pthread_mutex_lock(&philo->data->write);
	printf("%llu %d %s\n", timestamp, philo->id + 1, str);
	pthread_mutex_unlock(&philo->data->write);
	return (0);
}

int	philo_eat(t_philo *philo)
{
	if (check_time(philo))
		return (1);
	pthread_mutex_lock(&philo->check);
	gettimeofday(&philo->t_eat, 0);
	philo->nb_eat += 1;
	pthread_mutex_unlock(&philo->check);
	if (philo_print(philo, philo->t_eat, "is eating", 0))
		return (1);
	usleep(philo->data->t_eat * 1000);
	return (0);
}

void	take_forks(t_philo *philo)
{
	struct timeval	time;

	if (philo->data->nb_philo > 1 && philo->id == philo->data->nb_philo - 1)
		pthread_mutex_lock(
			&philo->data->forks[(philo->id + 1) % philo->data->nb_philo]);
	else
		pthread_mutex_lock(&philo->data->forks[philo->id]);
	gettimeofday(&time, 0);
	philo_print(philo, time, "has taken a fork", 0);
	if (philo->data->nb_philo == 1)
	{
		usleep((philo->data->t_die + 20) * 1000);
		return ;
	}
	if (philo->id == philo->data->nb_philo - 1)
		pthread_mutex_lock(&philo->data->forks[philo->id]);
	else
		pthread_mutex_lock(
			&philo->data->forks[(philo->id + 1) % philo->data->nb_philo]);
	gettimeofday(&time, 0);
	philo_print(philo, time, "has taken a fork", 0);
}

void	*philosopher(void *philo_v)
{
	struct timeval	time;
	t_philo			*philo;

	philo = (t_philo *)philo_v;
	if (philo->id % 2)
		usleep((philo->data->t_eat / 10) * 1000);
	while (!check_died(philo->data) && philo->nb_eat != philo->data->n_eat)
	{
		take_forks(philo);
		philo_eat(philo);
		pthread_mutex_unlock(&philo->data->forks[philo->id]);
		if (philo->data->nb_philo > 1)
			pthread_mutex_unlock(
				&philo->data->forks[(philo->id + 1) % philo->data->nb_philo]);
		gettimeofday(&time, 0);
		if (philo_print(philo, time, "is sleeping", 0))
			break ;
		usleep(philo->data->t_sleep * 1000);
		gettimeofday(&time, 0);
		philo_print(philo, time, "is thinking", 0);
		if (philo->data->nb_philo % 2)
			usleep(10000);
	}
	return (0);
}

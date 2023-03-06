/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:41:20 by afelten           #+#    #+#             */
/*   Updated: 2023/03/06 15:41:25 by afelten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <stdlib.h>

void	*philosopher(void *philo);
int		philo_print(t_philo *philo, struct timeval time,
			const char *str, int type);
int		destroy_all(t_data *data, int type, int n);
void	check_dead(t_data *data, int id);

void	check_end(t_data *data)
{
	int	i;
	int	eaten;

	i = 0;
	eaten = 0;
	while (!data->died && eaten < data->nb_philo)
	{
		if (i == data->nb_philo)
		{
			eaten = 0;
			i = 0;
			usleep(1000);
		}
		pthread_mutex_lock(&data->philos[i].check);
		check_dead(data, i);
		if (data->n_eat > 0 && data->philos[i].nb_eat == data->n_eat)
			eaten++;
		pthread_mutex_unlock(&data->philos[i].check);
		i++;
	}
}

int	launch_philos(t_data *data)
{
	int				i;
	struct timeval	time;

	data->philos_t = malloc(sizeof(pthread_t) * data->nb_philo);
	if (!data->philos_t)
		return (destroy_all(data, 3, data->nb_philo));
	i = -1;
	gettimeofday(&time, 0);
	data->t_start = time.tv_sec * 1000 + time.tv_usec / 1000;
	while (++i < data->nb_philo)
	{
		gettimeofday(&data->philos[i].t_eat, 0);
		if (pthread_create(&data->philos_t[i], 0,
				philosopher, &data->philos[i]))
		{
			pthread_mutex_lock(&data->check);
			data->died = 1;
			pthread_mutex_unlock(&data->check);
			return (destroy_all(data, 4, data->nb_philo));
		}
	}
	check_end(data);
	return (1);
}

int	init_philo(t_data *data, int id)
{
	if (pthread_mutex_init(&data->philos[id].check, 0))
		return (destroy_all(data, 3, id));
	data->philos[id].id = id;
	data->philos[id].nb_eat = 0;
	data->philos[id].data = data;
	return (1);
}

int	init_data(t_data *data)
{
	int	i;

	data->died = 0;
	if (pthread_mutex_init(&data->write, 0))
		return (0);
	if (pthread_mutex_init(&data->check, 0))
		return (destroy_all(data, 0, 0));
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->forks)
		return (destroy_all(data, 1, 0));
	i = -1;
	while (++i < data->nb_philo)
	{
		if (pthread_mutex_init(&data->forks[i], 0))
			return (destroy_all(data, 2, i));
	}
	data->philos = malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->philos)
		return (destroy_all(data, 2, i));
	i = -1;
	while (++i < data->nb_philo)
		if (!init_philo(data, i))
			return (0);
	return (1);
}

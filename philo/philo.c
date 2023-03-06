/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 16:56:03 by afelten           #+#    #+#             */
/*   Updated: 2023/02/19 19:44:51 by afelten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

int	init_data(t_data *data);
int	launch_philos(t_data *data);
int	get_nbr(const char *str);
int	print_err(const char *str);

int	parse_input(int argc, const char *argv[], t_data *data)
{
	data->nb_philo = get_nbr(argv[1]);
	data->t_die = get_nbr(argv[2]);
	data->t_eat = get_nbr(argv[3]);
	data->t_sleep = get_nbr(argv[4]);
	if (data->nb_philo <= 0 || data->t_die <= 0 || data->t_eat <= 0
		|| data->t_sleep <= 0 || data->nb_philo > 200)
		return (0);
	if (argc == 6)
		data->n_eat = get_nbr(argv[5]);
	else
		data->n_eat = -1;
	if (argc == 6 && data->n_eat <= 0)
		return (0);
	return (1);
}

int	destroy_forks(pthread_mutex_t *forks, int n)
{
	int	i;

	i = -1;
	while (++i < n)
		pthread_mutex_destroy(&forks[i]);
	free(forks);
	return (0);
}

int	destroy_philos(t_philo *philos, int n)
{
	int	i;

	i = -1;
	while (++i < n)
		pthread_mutex_destroy(&philos[i].check);
	free(philos);
	return (0);
}

int	destroy_all(t_data *data, int type, int n)
{
	pthread_mutex_destroy(&data->write);
	if (type > 0)
		pthread_mutex_destroy(&data->check);
	if (type == 2)
		destroy_forks(data->forks, n);
	else if (type > 2)
		destroy_forks(data->forks, data->nb_philo);
	if (type > 2)
		destroy_philos(data->philos, n);
	if (type > 3)
		free(data->philos_t);
	return (0);
}

int	main(int argc, const char *argv[])
{
	t_data	data;
	int		i;

	if (argc < 5 || argc > 6)
		return (print_err("Incorrect number of arguments\n"));
	if (!parse_input(argc, argv, &data))
		return (print_err("Incorrect arguments\n"));
	if (!init_data(&data))
		return (print_err("Error in initialisation\n"));
	if (!launch_philos(&data))
		return (print_err("Error in thread creation\n"));
	i = -1;
	while (++i < data.nb_philo)
		pthread_join(data.philos_t[i], 0);
	destroy_all(&data, 4, data.nb_philo);
	return (0);
}

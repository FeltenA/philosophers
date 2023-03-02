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

#include "philo_bonus.h"
#include <stdlib.h>
#include <sys/wait.h>

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
		|| data->t_sleep <= 0)
		return (0);
	if (argc == 6)
		data->n_eat = get_nbr(argv[5]);
	else
		data->n_eat = -1;
	if (argc == 6 && data->n_eat <= 0)
		return (0);
	return (1);
}

int	destroy_philos(t_philo *philos, int n)
{
	int	i;

	i = -1;
	while (++i < n)
		sem_close(philos[i].check);
	free(philos);
	return (0);
}

int	destroy_all(t_data *data, int type, int n)
{
	int	i;
	int	status;

	if (type == 3)
	{
		i = -1;
		if (data->n_eat > 0)
			kill(data->p_eaten, SIGKILL);
		while (++i < n)
			kill(data->philos[i].pid, SIGKILL);
		i = -1;
		if (data->n_eat > 0)
			waitpid(data->p_eaten, &status, 0);
		while (++i < n)
			waitpid(data->philos[i].pid, &status, 0);
	}
	sem_close(data->finish);
	sem_close(data->write);
	sem_close(data->eaten);
	sem_close(data->forks);
	if (type == 1)
		destroy_philos(data->philos, n);
	else if (type > 1)
		destroy_philos(data->philos, data->nb_philo);
	return (0);
}

int	main(int argc, const char *argv[])
{
	t_data	data;

	if (argc < 5 || argc > 6)
		return (print_err("Incorrect number of arguments\n"));
	if (!parse_input(argc, argv, &data))
		return (print_err("Incorrect arguments\n"));
	if (!init_data(&data))
		return (print_err("Error in initialisation\n"));
	if (!launch_philos(&data))
		return (print_err("Error in process creation\n"));
	sem_wait(data.finish);
	destroy_all(&data, 3, data.nb_philo);
	return (0);
}

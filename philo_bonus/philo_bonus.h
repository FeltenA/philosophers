/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:43:22 by afelten           #+#    #+#             */
/*   Updated: 2023/03/06 15:43:26 by afelten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <sys/time.h>
# include <fcntl.h>
# include <semaphore.h>
# include <pthread.h>
# include <signal.h>

struct	s_data;

typedef struct s_philo
{
	int					id;
	pid_t				pid;
	int					nb_eat;
	struct timeval		t_eat;
	struct s_data		*data;
	sem_t				*check;
}	t_philo;

typedef struct s_data
{
	int					nb_philo;
	int					t_die;
	int					t_eat;
	int					t_sleep;
	int					n_eat;
	unsigned long long	t_start;
	pid_t				p_eaten;
	sem_t				*write;
	sem_t				*finish;
	sem_t				*eaten;
	sem_t				*forks;
	t_philo				*philos;
}	t_data;

#endif

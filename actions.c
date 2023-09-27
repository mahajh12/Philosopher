/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malhamel <malhamel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 15:34:22 by malhamel          #+#    #+#             */
/*   Updated: 2023/09/20 16:05:35 by malhamel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_philo *philo)
{
	long	current_time;

	current_time = timestamp();
	pthread_mutex_lock(&philo->data->is_died);
	if (philo->data->num_of_philo == 1)
	{
		usleep_mili(philo->data->time_to_die);
		print_msg("has died", philo, 0xFD8A8A);
		return (1);
	}
	if (!philo->data->stop && (current_time
			- philo->last_eaten > philo->data->time_to_die))
	{
		print_msg("has died", philo, 0xFD8A8A);
		philo->data->stop = 1;
		pthread_mutex_unlock(&philo->data->is_died);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->is_died);
	if (philo->data->stop)
		return (1);
	return (0);
}

void	pick_fork(t_philo *philo)
{
	int	left_fork;
	int	right_fork;

	left_fork = philo->left_fork;
	right_fork = philo->right_fork;
	pthread_mutex_lock(&(philo->data->fork_mutex[left_fork]));
	pthread_mutex_lock(&(philo->data->fork_mutex[right_fork]));
	print_msg("has taken a fork", philo, 0x9EA1D4);
	print_msg("has taken a fork", philo, 0x9EA1D4);
}

void	eating(t_philo *philo)
{
	int	eat_dur;

	eat_dur = philo->data->time_to_eat;
	philo->num_eaten++;
	print_msg("is eating", philo, 0xFFCBCC);
	ft_usleep(eat_dur, philo);
	philo->last_eaten = timestamp();
	pthread_mutex_unlock(&(philo->data->fork_mutex[philo->left_fork]));
	pthread_mutex_unlock(&(philo->data->fork_mutex[philo->right_fork]));
}

void	sleep_think(t_philo *philo)
{
	int	sleep_dur;

	sleep_dur = philo->data->time_to_sleep;
	print_msg("is sleeping", philo, 0xDFEBEB);
	ft_usleep(sleep_dur, philo);
	print_msg("is thinking", philo, 0xF1F7B5);
}

void	*philo_threads(void *philo)
{
	t_philo	*phil;

	phil = (t_philo *)philo;
	phil->last_eaten = timestamp();
	phil->s_routine = timestamp();
	while (!phil->data->stop)
	{
		if (check_death(phil))
			break ;
		if (phil->data->must_eat > 0 && phil->num_eaten >= phil->data->must_eat)
			break ;
		if (phil->data->stop)
			break ;
		pick_fork(phil);
		eating(phil);
		if (phil->data->stop)
			break ;
		sleep_think(phil);
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malhamel <malhamel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 15:34:49 by malhamel          #+#    #+#             */
/*   Updated: 2023/09/18 15:48:34 by malhamel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutexes(t_data *philo)
{
	int	i;

	i = 0;
	while (i < philo->num_of_philo)
	{
		pthread_join(philo->philos_thread[i], NULL);
		i++;
	}
	i = 0;
	while (i < philo->num_of_philo)
	{
		pthread_mutex_destroy(&philo->fork_mutex[i]);
		i++;
	}
	pthread_mutex_destroy(&philo->is_thinking);
	pthread_mutex_destroy(&philo->is_eating);
	pthread_mutex_destroy(&philo->is_died);
	pthread_mutex_destroy(&philo->is_sleeping);
}

void	init_mutex(t_data *philo)
{
	int	i;

	i = 0;
	while (i < philo->num_of_philo)
	{
		pthread_mutex_init(&philo->fork_mutex[i], NULL);
		i++;
	}
	pthread_mutex_init(&philo->is_printing, NULL);
	pthread_mutex_init(&philo->is_thinking, NULL);
	pthread_mutex_init(&philo->is_eating, NULL);
	pthread_mutex_init(&philo->is_died, NULL);
	pthread_mutex_init(&philo->is_sleeping, NULL);
}

int	init_philo(t_data *philo)
{
	int	i;

	i = 0;
	philo->stop = 0;
	while (i < philo->num_of_philo)
	{
		philo->philos[i].id = i + 1;
		philo->philos[i].eaten = 0;
		philo->philos[i].has_died = 0;
		philo->philos[i].num_eaten = 0;
		philo->philos[i].left_fork = i;
		philo->philos[i].right_fork = (i + 1) % philo->num_of_philo;
		philo->philos[i].data = philo;
		philo->philos[i].last_eaten = 0;
		pthread_create(&philo->philos_thread[i], NULL, philo_threads,
			(void *)&philo->philos[i]);
		i++;
	}
	return (0);
}

int	check_digit(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (!(ft_isdigit(av[i][j])))
			{
				error_message("Please only enter numbers");
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	parse(char **av, int ac, t_data *philo)
{
	(void)ac;
	if (check_digit(av))
		return (1);
	philo->num_of_philo = ft_atoi(av[1]);
	philo->time_to_die = ft_atoi(av[2]);
	philo->time_to_eat = ft_atoi(av[3]);
	philo->time_to_sleep = ft_atoi(av[4]);
	if (philo->num_of_philo > 200 || philo->num_of_philo == 0
		|| philo->time_to_die < 60 || philo->time_to_sleep < 60
		|| philo->time_to_eat < 60)
	{
		error_message("Wrong inputs");
		return (1);
	}
	if (ac == 6)
	{
		philo->must_eat = ft_atoi(av[5]);
		if (philo->must_eat <= 0)
			return (1);
	}
	else
		philo->must_eat = 0;
	return (0);
}

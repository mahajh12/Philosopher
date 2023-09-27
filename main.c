/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malhamel <malhamel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 15:34:35 by malhamel          #+#    #+#             */
/*   Updated: 2023/09/18 15:49:37 by malhamel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	philo;

	if (ac != 5 && ac != 6)
	{
		error_message("Please enter the proper number of arguments");
		return (1);
	}
	if (parse(av, ac, &philo))
		return (1);
	init_mutex(&philo);
	init_philo(&philo);
	destroy_mutexes(&philo);
	return (0);
}

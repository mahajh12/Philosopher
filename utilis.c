/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilis.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malhamel <malhamel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 15:34:53 by malhamel          #+#    #+#             */
/*   Updated: 2023/09/18 15:34:54 by malhamel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(int ms, t_philo *philo)
{
	long int	time;

	time = timestamp();
	while (timestamp() - time < ms && !philo->data->stop && !check_death(philo))
		usleep(ms / 10);
}

int	error_msg(void)
{
	printf("\033[1;31mError\033[0m\n");
	return (1);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
	{
		return (1);
	}
	return (0);
}

int	ft_atoi(const char *str)
{
	int	sign;
	int	res;
	int	i;

	i = 0;
	res = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= 8 && str[i] <= 13))
		i++;
	if (str[i] == '-')
	{
		if (str[i + 1] == '+')
			return (0);
		error_msg();
	}
	if (str[i] == '+')
		i++;
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		if (res > 2147483647 || (res == 2147483647 && str[i] - '0' > 7))
			error_msg();
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (sign * res);
}

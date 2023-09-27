/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilis2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malhamel <malhamel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 15:34:58 by malhamel          #+#    #+#             */
/*   Updated: 2023/09/18 16:02:53 by malhamel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	print_msg(char *text, t_philo *philo, int r, int g, int b)
// {
// 	pthread_mutex_lock(&philo->data->is_printing);
// 	if (!philo->data->stop)
// 		printf("\033[38;2;%d;%d;%dm%lld %d %s\033[0m\n", r, g, b, (timestamp()
// 				- philo->s_routine), philo->id, text);
// 	pthread_mutex_unlock(&philo->data->is_printing);
// }

void	print_msg(char *text, t_philo *philo, int color)
{
	pthread_mutex_lock(&philo->data->is_printing);
	if (!philo->data->stop)
	{
		printf("\033[38;2;%d;%d;%dm%lld %d %s\033[0m\n", (color >> 16) & 0xFF,
			(color >> 8) & 0xFF, color & 0xFF, (timestamp() - philo->s_routine),
			philo->id, text);
	}
	pthread_mutex_unlock(&philo->data->is_printing);
}

void	usleep_mili(int ms)
{
	long int	time;

	time = timestamp();
	while (timestamp() - time < ms)
		usleep(ms / 10);
}

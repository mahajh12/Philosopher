/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malhamel <malhamel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 15:49:16 by malhamel          #+#    #+#             */
/*   Updated: 2023/09/18 16:03:52 by malhamel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct data		t_data;

typedef struct philosopher
{
	int					id;
	int					eaten;
	int					has_died;
	int					left_fork;
	int					right_fork;
	int					num_eaten;
	long				last_eaten;
	long				s_routine;
	t_data				*data;
}						t_philo;

typedef struct data
{
	int					num_of_philo;
	int					time_to_sleep;
	int					time_to_die;
	int					time_to_eat;
	int					must_eat;
	int					stop;
	struct philosopher	philos[200];
	int					fork[200];
	pthread_mutex_t		fork_mutex[200];
	pthread_mutex_t		is_thinking;
	pthread_mutex_t		is_eating;
	pthread_mutex_t		is_died;
	pthread_mutex_t		is_sleeping;
	pthread_mutex_t		is_printing;
	pthread_t			philos_thread[200];
}						t_data;

int						ft_atoi(const char *str);
int						parse(char **av, int ac, t_data *philo);
int						ft_isdigit(int c);
int						error_msg(void);
int						init_philo(t_data *philo);
int						check_death(t_philo *philo);
long long				timestamp(void);
void					pick_fork(t_philo *philo);
void					eating(t_philo *philo);
void					sleep_think(t_philo *philo);
void					*philo_threads(void *philo);
void					destroy_mutexes(t_data *philo);
void					init_mutex(t_data *philo);
void					usleep_mili(int ms);
void					ft_usleep(int ms, t_philo *philo);
void					print_msg(char *text, t_philo *philo, int color);
void					error_message(char *str);

#endif
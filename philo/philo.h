/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-pee <mvan-pee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 14:42:17 by mvan-pee          #+#    #+#             */
/*   Updated: 2024/01/19 13:55:12 by mvan-pee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

enum				e_action
{
	FORK,
	EAT,
	SLEEP,
	THINK,
	DIED
};

typedef struct s_info
{
	unsigned int	number_of_philo;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	int				number_of_times;
}					t_info;

typedef struct s_philo
{
	unsigned int	id;
	unsigned int	last_eat;
	unsigned int	nbr_eat;
	pthread_t		thread;
	pthread_mutex_t	fork;
	bool			dead;
}					t_philo;

typedef struct s_data
{
	unsigned int	start_time;
	t_info			info;
	t_philo			*philo;
	pthread_mutex_t	mutex_print;
	pthread_mutex_t	mutex_data;
	pthread_mutex_t	mutex_eat;
	pthread_mutex_t	mutex_time;
}					t_data;

typedef struct s_all
{
	t_data			*data;
	unsigned int	index;
}					t_all;

/* Main function for threading*/
bool				threading(t_data *data);
void				print(t_data *data, int index, int code);
void				takefork(t_data *data, int index1, int index2);
void				eating(t_data *data, int index1, int index2);
void				sleeping(t_data *data, int index);

/* Utils */
int					ft_atoi(const char *nptr);
int					get_time(t_data *data);
void				ft_sleep(t_data *data, int time);
bool				has_died(t_data *data);
bool				check_last_eat(t_data *data, int index);
t_all				*get_all_informations(t_data *data);

#endif
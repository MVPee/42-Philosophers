/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 14:42:17 by mvan-pee          #+#    #+#             */
/*   Updated: 2024/01/12 15:01:07 by mvpee            ###   ########.fr       */
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
	int				number_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times;
}					t_info;

typedef struct s_philo
{
	int				id;
	int				last_eat;
	int				nbr_eat;
	pthread_t		thread;
	pthread_mutex_t	fork;
	bool			dead;
}					t_philo;

typedef struct s_data
{
	int				start_time;
	t_info			info;
	t_philo			*philo;
	pthread_mutex_t	mutex_print;
	pthread_mutex_t	mutex_fork;
	pthread_mutex_t	mutex_eat;
	pthread_mutex_t	mutex_data;
}					t_data;

typedef struct s_all
{
	t_data			*data;
	int				index;
}					t_all;

/* Main function for threading*/
bool				threading(t_data *data);
void				print(t_data *data, int index, int code);
bool				takefork(t_data *data, int index1, int index2);
void				eating(t_data *data, int index1, int index2);
void				sleeping(t_data *data, int index);

/* Initialisation */
bool				init_info(t_data *data, char **args);
bool				init_philo(t_data *data);

/* Utils */
int					ft_atoi(const char *nptr);
int					get_time(t_data *data);
void				ft_sleep(t_data *data, int time);
bool				is_died(t_data *data);
bool				check_last_eat(t_data *data, int index);

#endif
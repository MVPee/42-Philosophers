/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-pee <mvan-pee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 14:42:17 by mvan-pee          #+#    #+#             */
/*   Updated: 2024/01/10 10:39:55 by mvan-pee         ###   ########.fr       */
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
	int				time;
	int				last_eat;
	pthread_t		thread;
	pthread_mutex_t	fork;
	bool			dead;
}					t_philo;

typedef struct s_data
{
	t_info			info;
	t_philo			*philo;
	pthread_mutex_t	mutex_print;
	pthread_mutex_t	fork;
}					t_data;

typedef struct s_all
{
	t_data			*data;
	int				index;
}					t_all;

/* Main function for threading*/


/* Initialisation */
bool				init_info(t_data *data, char **args);
bool				init_philo(t_data *data);

/* Utils */
int					ft_atoi(const char *nptr);
void				ft_clean(t_data *data);
long				get_time(void);
void				ft_sleep(int ms);

#endif
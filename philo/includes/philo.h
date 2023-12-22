/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 14:42:17 by mvan-pee          #+#    #+#             */
/*   Updated: 2023/12/22 14:49:40 by mvpee            ###   ########.fr       */
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
	pthread_t		thread;
	bool			fork;
}					t_philo;

typedef struct s_data
{
	int				test;
	t_info			info;
	t_philo			*philo;
	pthread_mutex_t	mutex_eat;
}					t_data;

/* Main function for threading*/
int					threading(t_data *data);

/* Initialisation */
bool				init_info(t_data *data, char **args);
bool				init_philo(t_data *data);

/* Utils */
int					ft_atoi(const char *nptr);
void				ft_clean(t_data *data);

#endif
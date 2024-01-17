/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 14:01:43 by mvpee             #+#    #+#             */
/*   Updated: 2024/01/17 18:15:22 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

bool	init_philo(t_data *data)
{
	int	i;

	data->philo = (t_philo *)malloc(sizeof(t_philo) \
		* data->info.number_of_philo);
	if (!data->philo)
		return (printf("malloc failed...\n"), true);
	i = -1;
	while (++i < data->info.number_of_philo)
	{
		data->philo[i].id = i + 1;
		data->philo[i].last_eat = 0;
		data->philo[i].nbr_eat = 0;
		data->philo[i].dead = false;
		data->philo[i].eating = false;
		pthread_mutex_init(&data->philo[i].fork, NULL);
	}
	pthread_mutex_init(&data->mutex_fork, NULL);
	pthread_mutex_init(&data->mutex_print, NULL);
	pthread_mutex_init(&data->mutex_eat, NULL);
	pthread_mutex_init(&data->mutex_data, NULL);
	return (false);
}

bool	init_info(t_data *data, char **args)
{
	int		temp;
	int		i;
	t_info	info;

	i = 0;
	while (args[i])
	{
		temp = ft_atoi(args[i]);
		if (!temp || temp < 0)
			return (printf("Invalid argument: %d.\n", i + 1), true);
		i++;
	}
	info.number_of_philo = ft_atoi(args[0]);
	info.time_to_die = ft_atoi(args[1]);
	info.time_to_eat = ft_atoi(args[2]);
	info.time_to_sleep = ft_atoi(args[3]);
	info.number_of_times = -1;
	if (args[4])
		info.number_of_times = ft_atoi(args[4]);
	data->info = info;
	data->philo = NULL;
	data->start_time = 0;
	return (false);
}

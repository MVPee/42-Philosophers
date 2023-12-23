/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 14:46:25 by mvpee             #+#    #+#             */
/*   Updated: 2023/12/23 11:55:05 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void eating(t_data *data, int index1, int index2)
{
	pthread_mutex_lock(&data->mutex_print);
	printf("%d is eating\n", data->philo[index1].id);
	pthread_mutex_unlock(&data->mutex_print);
	usleep(data->info.time_to_eat);
	pthread_mutex_unlock(&data->philo[index1].fork);
	pthread_mutex_unlock(&data->philo[index2].fork);
}

static bool takefork(t_data *data, int index1, int index2)
{
    if (pthread_mutex_lock(&data->philo[index1].fork) != 0) {
        return false;
    }
    if (pthread_mutex_lock(&data->philo[index2].fork) != 0) {
        pthread_mutex_unlock(&data->philo[index1].fork);
        return false;
    }
    pthread_mutex_lock(&data->mutex_print);
	printf("%d has taken fork\n", data->philo[index1].id);
	pthread_mutex_unlock(&data->mutex_print);
    return true;
}

static void	*routine(void *args)
{
	t_all	*all;
	int		index1;
	int		index2;
	t_data	*data;

	all = (t_all *)args;
	index1 = all->index;
	data = all->data;
	if (index1 == 0)
		index2 = data->info.number_of_philo - 1;
	else if (index1 == data->info.number_of_philo - 1)
		index2 = 0;
	else
		index2 = index1 - 1;
	while (!is_dead(data))
	{
		if (takefork(data, index1, index2))
			eating(data, index1, index2);
		
		pthread_mutex_lock(&data->mutex_print);
		printf("%d is sleeping\n", data->philo[index1].id);
		pthread_mutex_unlock(&data->mutex_print);
		usleep(data->info.time_to_sleep);
		
		pthread_mutex_lock(&data->mutex_print);
		printf("%d is thinking\n", data->philo[index1].id);
		pthread_mutex_unlock(&data->mutex_print);
	}
	return (NULL);
}

bool	threading(t_data *data)
{
	t_all	*all;
	int		i;

	all = (t_all *)malloc(sizeof(t_all) * data->info.number_of_philo);
	if (!all)
		return (printf("malloc failed...\n"), true);
	i = -1;
	while (++i < data->info.number_of_philo)
	{
		all[i].data = data;
		all[i].index = i;
	}
	pthread_mutex_init(&data->mutex_print, NULL);
	i = -1;
	while (++i < data->info.number_of_philo)
	{
		if (pthread_create(&data->philo[i].thread, NULL, &routine,
				&all[i]) != 0)
			return (free(all), printf("pthread create failed...\n"), true);
	}
	i = -1;
	while (++i < data->info.number_of_philo)
		if (pthread_join(data->philo[i].thread, NULL) != 0)
			return (free(all), printf("pthread join failed...\n"), true);
	return (free(all), false);
}

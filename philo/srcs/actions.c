/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-pee <mvan-pee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 15:48:45 by mvpee             #+#    #+#             */
/*   Updated: 2024/01/10 08:28:44 by mvan-pee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void thinking(t_data *data, int index1)
{
    pthread_mutex_lock(&data->mutex_print);
    printf("%dms %d is thinking\n", data->philo[index1].time, data->philo[index1].id);
    pthread_mutex_unlock(&data->mutex_print);
}

void sleeping(t_data *data, int index1)
{
	pthread_mutex_lock(&data->mutex_print);
    printf("%dms %d is sleeping\n", data->philo[index1].time, data->philo[index1].id);
    data->philo[index1].last_eat += data->info.time_to_sleep;
    data->philo[index1].time += data->info.time_to_sleep;
    pthread_mutex_unlock(&data->mutex_print);
    usleep(data->info.time_to_sleep);
}

void eating(t_data *data, int index1, int index2)
{
	pthread_mutex_lock(&data->mutex_print);
	printf("%dms %d is eating\n", data->philo[index1].time, data->philo[index1].id);
    data->philo[index1].last_eat = 0;
    data->philo[index1].time += data->info.time_to_eat;
	pthread_mutex_unlock(&data->mutex_print);
	usleep(data->info.time_to_eat);
	pthread_mutex_unlock(&data->philo[index1].fork);
	pthread_mutex_unlock(&data->philo[index2].fork);
}

bool takefork(t_data *data, int index1, int index2)
{
    if (data->info.number_of_philo == 1)
        return false;
    pthread_mutex_lock(&data->fork);
    if (pthread_mutex_lock(&data->philo[index1].fork) != 0) {
        return false;
    }
    if (pthread_mutex_lock(&data->philo[index2].fork) != 0) {
        pthread_mutex_unlock(&data->philo[index1].fork);
        return false;
    }
    pthread_mutex_unlock(&data->fork);
    pthread_mutex_lock(&data->mutex_print);
	printf("%dms %d has taken fork\n", data->philo[index1].time, data->philo[index1].id);
	pthread_mutex_unlock(&data->mutex_print);
    return true;
}

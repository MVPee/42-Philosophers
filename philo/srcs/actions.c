/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-pee <mvan-pee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 15:48:45 by mvpee             #+#    #+#             */
/*   Updated: 2024/01/10 10:15:42 by mvan-pee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void thinking(t_data *data, int index1)
{
    pthread_mutex_lock(&data->mutex_print);
    printf("%ld %d is thinking\n", get_time(), data->philo[index1].id);
    pthread_mutex_unlock(&data->mutex_print);
}

void sleeping(t_data *data, int index1)
{
	pthread_mutex_lock(&data->mutex_print);
    printf("%ld %d is sleeping\n", get_time(), data->philo[index1].id);
    data->philo[index1].last_eat = get_time();
    data->philo[index1].time += data->info.time_to_sleep;
    if (data->philo->last_eat + data->info.time_to_sleep > data->info.time_to_die)
    {
        printf("%ld %d is dead\n", get_time() + data->info.time_to_die - data->info.time_to_sleep, data->philo[index1].id);
        data->philo[index1].dead = true;
        pthread_mutex_unlock(&data->mutex_print);
        return ;
    }
    pthread_mutex_unlock(&data->mutex_print);
    ft_sleep(data->info.time_to_sleep);
}

void eating(t_data *data, int index1, int index2)
{
	pthread_mutex_lock(&data->mutex_print);
	printf("%ld %d is eating\n", get_time(), data->philo[index1].id);
    data->philo[index1].last_eat = get_time();
    data->philo[index1].time += data->info.time_to_eat;
	pthread_mutex_unlock(&data->mutex_print);
	ft_sleep(data->info.time_to_eat);
	pthread_mutex_unlock(&data->philo[index1].fork);
	pthread_mutex_unlock(&data->philo[index2].fork);
}

bool takefork(t_data *data, int index1, int index2)
{
    if (data->info.number_of_philo == 1)
        return false;
    pthread_mutex_lock(&data->fork);
    if (pthread_mutex_lock(&data->philo[index1].fork) != 0) {
        pthread_mutex_unlock(&data->fork);
        return false;
    }
    if (pthread_mutex_lock(&data->philo[index2].fork) != 0) {
        pthread_mutex_unlock(&data->philo[index1].fork);
        pthread_mutex_unlock(&data->fork);
        return false;
    }
    pthread_mutex_unlock(&data->fork);
    pthread_mutex_lock(&data->mutex_print);
	printf("%ld %d has taken fork\n", get_time(), data->philo[index1].id);
	pthread_mutex_unlock(&data->mutex_print);
    return true;
}

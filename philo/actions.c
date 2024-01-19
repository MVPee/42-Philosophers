/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-pee <mvan-pee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 14:14:26 by mvpee             #+#    #+#             */
/*   Updated: 2024/01/19 13:55:12 by mvan-pee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print(t_data *data, int index, int code)
{
	pthread_mutex_lock(&data->mutex_print);
	if (code == FORK && !has_died(data))
		printf("%d %d has taken a fork\n", get_time(data), index + 1);
	else if (code == EAT && !has_died(data))
		printf("%d %d is eating\n", get_time(data), index + 1);
	else if (code == SLEEP && !has_died(data))
		printf("%d %d is sleeping\n", get_time(data), index + 1);
	else if (code == THINK && !has_died(data))
		printf("%d %d is thinking\n", get_time(data), index + 1);
	else if (code == DIED && !has_died(data))
	{
		printf("%d %d died\n", get_time(data), index + 1);
		pthread_mutex_lock(&data->mutex_data);
		data->philo[index].dead = true;
		pthread_mutex_unlock(&data->mutex_data);
	}
	pthread_mutex_unlock(&data->mutex_print);
}

void	takefork(t_data *data, int index1, int index2)
{
	pthread_mutex_lock(&data->philo[index1].fork);
	print(data, index1, FORK);
	pthread_mutex_lock(&data->philo[index2].fork);
	print(data, index1, FORK);
}

void	eating(t_data *data, int index1, int index2)
{
	print(data, index1, EAT);
	pthread_mutex_lock(&data->mutex_eat);
	data->philo[index1].last_eat = get_time(data);
	data->philo[index1].nbr_eat += 1;
	pthread_mutex_unlock(&data->mutex_eat);
	ft_sleep(data, data->info.time_to_eat);
	pthread_mutex_unlock(&data->philo[index2].fork);
	pthread_mutex_unlock(&data->philo[index1].fork);
}

void	sleeping(t_data *data, int index)
{
	print(data, index, SLEEP);
	ft_sleep(data, data->info.time_to_sleep);
}

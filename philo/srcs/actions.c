/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 14:14:26 by mvpee             #+#    #+#             */
/*   Updated: 2024/01/17 18:34:42 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	print(t_data *data, int index, int code)
{
	pthread_mutex_lock(&data->mutex_print);
	if (code == FORK && !is_died(data))
		printf("%d %d has taken a fork\n", get_time(data), index + 1);
	else if (code == EAT && !is_died(data))
		printf("%d %d is eating\n", get_time(data), index + 1);
	else if (code == SLEEP && !is_died(data))
		printf("%d %d is sleeping\n", get_time(data), index + 1);
	else if (code == THINK && !is_died(data))
		printf("%d %d is thinking\n", get_time(data), index + 1);
	else if (code == DIED && !is_died(data))
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
	data->philo[index1].eating = true;
	data->philo[index1].last_eat = get_time(data);
	data->philo[index1].nbr_eat += 1;
	ft_sleep(data, data->info.time_to_eat);
	pthread_mutex_unlock(&data->philo[index2].fork);
	pthread_mutex_unlock(&data->philo[index1].fork);
	data->philo[index1].eating = false;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-pee <mvan-pee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 09:54:57 by mvan-pee          #+#    #+#             */
/*   Updated: 2024/01/12 11:04:16 by mvan-pee         ###   ########.fr       */
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
		printf("%d %d is died\n", get_time(data), index + 1);
		data->philo[index].dead = true;
	}
	pthread_mutex_unlock(&data->mutex_print);
}

bool	takefork(t_data *data, int index1, int index2)
{
	pthread_mutex_lock(&data->mutex_fork);
	if (data->info.number_of_philo == 1)
	{
		pthread_mutex_unlock(&data->mutex_fork);
		return (false);
	}
	check_last_eat(data, index1);
	pthread_mutex_lock(&data->philo[index1].fork);
	check_last_eat(data, index1);
	print(data, index1, FORK);
	pthread_mutex_lock(&data->philo[index2].fork);
	check_last_eat(data, index1);
	print(data, index1, FORK);
	pthread_mutex_unlock(&data->mutex_fork);
	return (true);
}

void	eating(t_data *data, int index1, int index2)
{
	print(data, index1, EAT);
	ft_sleep(data, data->info.time_to_eat);
	data->philo[index1].last_eat = get_time(data);
	data->philo[index1].nbr_eat += 1;
	pthread_mutex_unlock(&data->philo[index1].fork);
	pthread_mutex_unlock(&data->philo[index2].fork);
}

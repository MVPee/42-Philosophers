/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-pee <mvan-pee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 10:43:13 by mvan-pee          #+#    #+#             */
/*   Updated: 2024/01/19 11:22:43 by mvan-pee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	get_left_index(t_data *data, int index)
{
	if (index == 0)
		return (data->info.number_of_philo - 1);
	return (index - 1);
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
	index2 = get_left_index(data, index1);
	data->philo[index1].last_eat = get_time(data);
	if (data->philo[index1].id % 2 == 0)
		ft_sleep(data, data->info.time_to_eat / 10);
	while (!is_died(data))
	{
		if (data->info.number_of_philo != 1)
		{
			takefork(data, index1, index2);
			eating(data, index1, index2);
			if ((int) data->philo[index1].nbr_eat == data->info.number_of_times)
				return (NULL);
		}
		sleeping(data, index1);
		print(data, index1, THINK);
	}
	return (NULL);
}

static bool	eat_enought(t_data *data)
{
	int	i;

	if (data->info.number_of_times == -1)
		return (false);
	i = -1;
	while (++i < (int) data->info.number_of_philo)
		if ((int) data->philo[i].nbr_eat != data->info.number_of_times)
			return (false);
	pthread_mutex_lock(&data->mutex_data);
	data->philo[0].dead = true;
	pthread_mutex_unlock(&data->mutex_data);
	return (true);
}

static void	*manager_philosophers(void *args)
{
	t_data	*data;
	int		i;
	int		now;

	data = (t_data *)args;
	while (69)
	{
		i = -1;
		while (++i < (int) data->info.number_of_philo)
		{
			now = get_time(data);
			pthread_mutex_lock(&data->mutex_eat);
			if (now - data->philo[i].last_eat >= data->info.time_to_die)
			{
				print(data, i, DIED);
				return (pthread_mutex_unlock(&data->mutex_eat), NULL);
			}
			pthread_mutex_unlock(&data->mutex_eat);
			if (eat_enought(data))
				return (NULL);
		}
	}
	return (NULL);
}

bool	threading(t_data *data)
{
	t_all		*all;
	int			i;
	pthread_t	manager;

	all = get_all_information(data);
	if (!all)
		return (true);
	i = -1;
	while (++i < (int) data->info.number_of_philo)
	{
		if (pthread_create(&data->philo[i].thread, NULL, &routine,
				&all[i]) != 0)
			return (free(all), printf("pthread create failed...\n"), true);
	}
	if (pthread_create(&manager, NULL, &manager_philosophers, data) != 0)
		return (free(all), printf("pthread create failed...\n"), true);
	i = -1;
	while (++i < (int) data->info.number_of_philo)
		if (pthread_join(data->philo[i].thread, NULL) != 0)
			return (free(all), printf("pthread join failed...\n"), true);
	if (pthread_join(manager, NULL) != 0)
		return (free(all), printf("pthread join failed...\n"), true);
	return (free(all), false);
}

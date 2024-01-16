/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-pee <mvan-pee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 10:43:13 by mvan-pee          #+#    #+#             */
/*   Updated: 2024/01/16 15:45:51 by mvan-pee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	get_left_index(t_data *data, int index)
{
	if (index == 0)
		return (data->info.number_of_philo - 1);
	else if (index == data->info.number_of_philo - 1)
		return (0);
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
	while (!is_died(data))
	{
		printf("t\n");
	}
	return (NULL);
}

static void *check_philosophers(void *args)
{
	t_data *data;
	data = (t_data *)args;
	int i;
	int now;

	while(true)
	{
		i = -1;
		while(++i < data->info.number_of_philo)
		{
			now = get_time(data);
			if (now - data->philo[i].last_eat >= data->info.time_to_die)
			{
				data->philo[i].dead = true;
				printf("Manager: %d is dead\n", i);
				return (NULL);
			}
		}
	}
	return (NULL);
}

bool	threading(t_data *data)
{
	t_all	*all;
	int		i;
	pthread_t t;

	all = (t_all *)malloc(sizeof(t_all) * data->info.number_of_philo);
	if (!all)
		return (printf("malloc failed...\n"), true);
	i = -1;
	while (++i < data->info.number_of_philo)
	{
		all[i].data = data;
		all[i].index = i;
	}
	i = -1;
	while (++i < data->info.number_of_philo)
	{
		if (pthread_create(&data->philo[i].thread, NULL, &routine,
				&all[i]) != 0)
			return (free(all), printf("pthread create failed...\n"), true);
	}
	if (pthread_create(&t, NULL, &check_philosophers, data) != 0)
		return (free(all), printf("pthread create failed...\n"), true);
	i = -1;
	while (++i < data->info.number_of_philo)
		if (pthread_join(data->philo[i].thread, NULL) != 0)
			return (free(all), printf("pthread join failed...\n"), true);
	if (pthread_join(t, NULL) != 0)
			return (free(all), printf("pthread join failed...\n"), true);
	return (free(all), false);
}

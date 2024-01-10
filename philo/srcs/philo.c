/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-pee <mvan-pee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 14:46:25 by mvpee             #+#    #+#             */
/*   Updated: 2024/01/10 10:37:14 by mvan-pee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static bool check_last_eat(t_data *data, int index1)
{
	printf("debug: %d > %d\n", data->philo[index1].last_eat, data->info.time_to_die);
	if (data->philo[index1].last_eat > data->info.time_to_die)
	{
		pthread_mutex_lock(&data->mutex_print);
		printf("%ld %d is dead\n", get_time(), data->philo[index1].id);
		data->philo[index1].dead = true;
		pthread_mutex_unlock(&data->mutex_print);
		return (false);
	}
	return (true);
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
		if (check_last_eat(data, index1) && !is_dead(data))
			return NULL;
		sleeping(data, index1);
		if (check_last_eat(data, index1) && !is_dead(data))
			return NULL;
		thinking(data, index1);
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
	pthread_mutex_init(&data->fork, NULL);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 10:43:13 by mvan-pee          #+#    #+#             */
/*   Updated: 2024/01/17 15:28:10 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static bool	how_much_eat(t_data *data, int index)
{
	if (data->info.number_of_times == -1)
		return (false);
	if (data->philo[index].nbr_eat == data->info.number_of_times)
		return (true);
	return (false);
}

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
		if (takefork(data, index1, index2))
			eating(data, index1, index2);
		print(data, index1, SLEEP);
		ft_sleep(data, data->info.time_to_sleep);
		print(data, index1, THINK);
	}
	return (NULL);
}

static void *check_philosophers(void *args)
{
	t_data *data;
	data = (t_data *)args;
	int i;
	int now;

	while(69)
	{
		i = -1;
		while(++i < data->info.number_of_philo)
		{
			now = get_time(data);
			if (now - data->philo[i].last_eat >= data->info.time_to_die)
			{
				print(data, i, DIED);
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
	pthread_t manager;

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
	if (pthread_create(&manager, NULL, &check_philosophers, data) != 0)
		return (free(all), printf("pthread create failed...\n"), true);
	i = -1;
	while (++i < data->info.number_of_philo)
		if (pthread_join(data->philo[i].thread, NULL) != 0)
			return (free(all), printf("pthread join failed...\n"), true);
	if (pthread_join(manager, NULL) != 0)
			return (free(all), printf("pthread join failed...\n"), true);
	return (free(all), false);
}

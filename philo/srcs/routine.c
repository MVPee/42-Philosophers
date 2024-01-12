/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-pee <mvan-pee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 10:43:13 by mvan-pee          #+#    #+#             */
/*   Updated: 2024/01/12 11:10:38 by mvan-pee         ###   ########.fr       */
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
	while (!is_died(data))
	{
		if (takefork(data, index1, index2))
			eating(data, index1, index2);
		if (how_much_eat(data, index1))
			return (NULL);
		print(data, index1, SLEEP);
		ft_sleep(data, data->info.time_to_sleep);
		if (check_last_eat(data, index1))
			return (NULL);
		print(data, index1, THINK);
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

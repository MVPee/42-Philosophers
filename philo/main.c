/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 14:41:32 by mvan-pee          #+#    #+#             */
/*   Updated: 2024/01/18 10:31:01 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	init_philo(t_data *data)
{
	int	i;

	data->philo = (t_philo *)malloc(sizeof(t_philo) \
		* data->info.number_of_philo);
	if (!data->philo)
		return (printf("malloc failed...\n"), true);
	i = -1;
	while (++i < (int) data->info.number_of_philo)
	{
		data->philo[i].id = i + 1;
		data->philo[i].last_eat = 0;
		data->philo[i].nbr_eat = 0;
		data->philo[i].dead = false;
		pthread_mutex_init(&data->philo[i].fork, NULL);
	}
	return (false);
}

static bool	init_info(t_data *data, char **args)
{
	int		temp;
	int		i;
	t_info	info;

	i = -1;
	while (args[++i])
	{
		temp = ft_atoi(args[i]);
		if (!temp || temp < 0)
			return (printf("Invalid argument: %d.\n", i + 1), true);
	}
	info.number_of_philo = ft_atoi(args[0]);
	info.time_to_die = ft_atoi(args[1]);
	info.time_to_eat = ft_atoi(args[2]);
	info.time_to_sleep = ft_atoi(args[3]);
	info.number_of_times = -1;
	if (args[4])
		info.number_of_times = ft_atoi(args[4]);
	data->info = info;
	data->philo = NULL;
	data->start_time = 0;
	pthread_mutex_init(&data->mutex_print, NULL);
	pthread_mutex_init(&data->mutex_data, NULL);
	return (false);
}

static void	ft_clean(t_data *data)
{
	int	i;

	pthread_mutex_destroy(&data->mutex_print);
	pthread_mutex_destroy(&data->mutex_data);
	i = -1;
	while (++i < (int) data->info.number_of_philo)
		pthread_mutex_destroy(&data->philo[i].fork);
	free(data->philo);
}

int	main(int ac, char **av)
{
	t_data			data;

	if (ac != 5 && ac != 6)
		return (printf("Invalid number(s) of argument(s).\n"), -1);
	if (init_info(&data, av + 1))
		return (1);
	if (init_philo(&data))
		return (2);
	threading(&data);
	return (ft_clean(&data), 0);
}

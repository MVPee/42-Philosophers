/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 14:01:43 by mvpee             #+#    #+#             */
/*   Updated: 2023/12/22 17:11:11 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

bool	init_philo(t_data *data)
{
	int	i;

	data->philo = (t_philo *)malloc(sizeof(t_philo) \
		* data->info.number_of_philo);
	if (!data->philo)
		return (printf("malloc failed...\n"), true);
	i = -1;
	while (++i < data->info.number_of_philo)
	{
		data->philo[i].id = i + 1;
		data->philo[i].fork = true;
		data->philo[i].dead = true;
	}
	return (false);
}

bool	init_info(t_data *data, char **args)
{
	int		temp;
	int		i;
	t_info	info;

	i = 0;
	while (args[i])
	{
		temp = ft_atoi(args[i]);
		if (!temp || temp < 0)
			return (printf("Invalid argument: %d.\n", i + 1), true);
		i++;
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
	return (false);
}

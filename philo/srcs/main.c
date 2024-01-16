/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-pee <mvan-pee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 14:41:32 by mvan-pee          #+#    #+#             */
/*   Updated: 2024/01/16 14:02:45 by mvan-pee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	ft_clean(t_data *data)
{
	int	i;

	free(data->philo);
	pthread_mutex_destroy(&data->mutex_print);
	pthread_mutex_destroy(&data->mutex_fork);
	pthread_mutex_destroy(&data->mutex_eat);
	pthread_mutex_destroy(&data->mutex_data);
	i = -1;
	while (++i < data->info.number_of_philo)
		pthread_mutex_destroy(&data->philo[i].fork);
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

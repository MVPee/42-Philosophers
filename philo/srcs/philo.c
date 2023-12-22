/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 14:46:25 by mvpee             #+#    #+#             */
/*   Updated: 2023/12/22 14:59:20 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	*routine(void *arg)
{
	t_data	*data;
	int		temp;

	data = (t_data *)arg;
	temp = 0;
	pthread_mutex_lock(&data->mutex_eat);
	while (temp++ < 1000000)
		data->test++;
	pthread_mutex_unlock(&data->mutex_eat);
	return (NULL);
}

int	threading(t_data *data)
{
	int	i;

	pthread_mutex_init(&data->mutex_eat, NULL);
	data->test = 0;
	i = -1;
	while (++i < data->info.number_of_philo)
		if (pthread_create(&data->philo[i].thread, NULL, &routine, data) != 0)
			return (printf("pthread create failed...\n"), 1);
	i = -1;
	while (++i < data->info.number_of_philo)
		if (pthread_join(data->philo[i].thread, NULL) != 0)
			return (printf("pthread join failed...\n"), 1);
	printf("test: %d\n", data->test);
	return (0);
}

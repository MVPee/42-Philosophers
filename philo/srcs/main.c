/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 14:41:32 by mvan-pee          #+#    #+#             */
/*   Updated: 2023/12/22 12:20:27 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	init_info(t_data *data, char **args)
{
	int	temp;
	int	i;
	t_info	info;

	i = 0;
	while (args[i])
	{
		temp = ft_atoi(args[i]);
		if (!temp || temp < 0)
			return (printf("Invalid argument: %d.\n", i + 1), 1);
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
	data->philo = (pthread_t *)malloc(sizeof(pthread_t) * info.number_of_philo);
	if(!data->philo)
		return (1);
	return (0);
}

static void *routine(void *arg) {
    t_data *data = (t_data *)arg;
	int temp = 0;
	pthread_mutex_lock(&data->mutex_eat);
	while(temp++ < 1000000)
		data->test++;
	pthread_mutex_unlock(&data->mutex_eat);
}

static int init_thread(t_data *data)
{
	int i;

	pthread_mutex_init(&data->mutex_eat, NULL);
	data->test = 0;
	i = 0;
	while(i < data->info.number_of_philo)
	{
		if (pthread_create(&data->philo[i], NULL, &routine, data) != 0)
			return (1);
		i++;
	}
	i = 0;
	while(i < data->info.number_of_philo)
	{
		if (pthread_join(data->philo[i], NULL) != 0)
			return (1);
		i++;
	}
	printf("test: %d\n", data->test);
	return (0);
}

static void ft_clear(t_data *data)
{
	free(data->philo);
	pthread_mutex_destroy(&data->mutex_eat);
}

int	main(int ac, char **av)
{
	t_data data;

	if (ac != 5 && ac != 6)
		return (printf("Invalid number(s) of argument(s).\n"), 1);
	if (init_info(&data, av + 1))
		return (1);
	if (init_thread(&data))
		return (ft_clear(&data), 1);
	ft_clear(&data);
	return 0;
}

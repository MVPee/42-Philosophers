/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-pee <mvan-pee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 14:41:32 by mvan-pee          #+#    #+#             */
/*   Updated: 2023/12/20 15:42:35 by mvan-pee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	init_info(t_info *info, char **args)
{
	int	temp;
	int	i;

	i = 0;
	while (args[i])
	{
		temp = atoi(args[i]);
		if (!temp || temp < 0)
			return (printf("Invalid argument: %d.\n", i + 1), 1);
		i++;
	}
	info->number_of_philo = atoi(args[0]);
	info->time_to_die = atoi(args[1]);
	info->time_to_eat = atoi(args[2]);
	info->time_to_sleep = atoi(args[3]);
	info->number_of_times = -1;
	if (args[4])
		info->number_of_times = atoi(args[4]);
	return (0);
}

int	main(int ac, char **av)
{
	t_info	info;

	if (ac != 5 && ac != 6)
		return (printf("Invalid number(s) of argument(s).\n"));
	if (init_info(&info, av + 1))
		return (1);
	printf("Test\n");
	return (0);
}

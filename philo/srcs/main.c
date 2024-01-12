/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-pee <mvan-pee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 14:41:32 by mvan-pee          #+#    #+#             */
/*   Updated: 2024/01/12 09:44:30 by mvan-pee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int ac, char **av)
{
	t_data	data;
	struct timeval time;

	gettimeofday(&time, NULL);
	data.start_time = time.tv_sec * 1000 + time.tv_usec / 1000;
	if (ac != 5 && ac != 6)
		return (printf("Invalid number(s) of argument(s).\n"), -1);
	if (init_info(&data, av + 1))
		return (1);
	if (init_philo(&data))
		return (2);
	if (threading(&data))
		return (3);
	return (ft_clean(&data), 0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-pee <mvan-pee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 14:41:32 by mvan-pee          #+#    #+#             */
/*   Updated: 2024/01/10 10:47:58 by mvan-pee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 5 && ac != 6)
		return (printf("Invalid number(s) of argument(s).\n"), -1);
	if (init_info(&data, av + 1))
		return (1);
	if (init_philo(&data))
		return (2);
	return (ft_clean(&data), 0);
}

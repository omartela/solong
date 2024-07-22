/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_enemy2_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartela <omartela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 09:05:39 by omartela          #+#    #+#             */
/*   Updated: 2024/07/18 09:05:43 by omartela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long_bonus.h"

int	lcg(void)
{
	int seed;

	seed = 0;
	seed = (LCG_A * seed + LCG_C) % LCG_M;
	return (seed);
}

int	generate_random_number(int min, int max)
{
	return (min + (lcg() % (max - min + 1)));
}

char	get_direction_from_num(int number)
{
	if (number == 1)
		return ('u');
	if (number == 2)
		return ('d');
	if (number == 3)
		return ('l');
	if (number == 4)
		return ('r');
	return ('r');
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartela <omartela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 10:05:25 by omartela          #+#    #+#             */
/*   Updated: 2024/07/22 10:18:10 by omartela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

int	main(int argc, char *argv[])
{
	t_game		game;

	if (argc == 2)
	{
		game.filename = argv[1];
		if (init_game(&game))
		{
			mlx_key_hook(game.mlx, &ft_hook_movement, &game);
			mlx_loop(game.mlx);
			free_game_assets(&game);
			mlx_terminate(game.mlx);
		}
	}
	else
		error("Too few or too many arguments");
}

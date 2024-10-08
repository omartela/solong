/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartela <omartela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 08:55:50 by omartela          #+#    #+#             */
/*   Updated: 2024/07/18 08:55:53 by omartela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long_bonus.h"

void	close_window(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	free_game_assets(game);
}

int	main(int argc, char *argv[])
{
	t_game		game;

	if (argc == 2)
	{
		game.filename = argv[1];
		if (init_game(&game))
		{
			mlx_key_hook(game.mlx, &ft_hook_movement, &game);
			mlx_close_hook(game.mlx, &close_window, &game);
			mlx_loop(game.mlx);
			mlx_terminate(game.mlx);
		}
	}
	else
		error("Too few or too many arguments");
}

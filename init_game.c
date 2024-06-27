/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartela <omartela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 23:25:34 by omartela          #+#    #+#             */
/*   Updated: 2024/06/27 13:49:40 by omartela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

void	init_game_variables(t_game *game)
{
	game->players = 0;
	game->exits = 0;
	game->collectibles = 0;
	game->move_count = 0;
	game->score = 0;
}

int	init_game(t_game *game)
{
	mlx_t		*mlx;
	t_list		*llist;

	llist = NULL;
	init_game_variables(game);
	if (!read_map(game))
		return (0);
	if (!validate_map(game))
	{
		free_map(game->map, game->map_height);
		return (0);
	}
	mlx = mlx_init(game->map_height * TILE_SIZE + TILE_SIZE, game->map_width * TILE_SIZE + TILE_SIZE, "Dwarf & Diamonds", true);
	if (!mlx)
		error("Failed to initialize mlx");
	game->mlx = mlx;
	init_game_images(game, &llist);
	extract_map_data(game, &llist);
	game->llist = llist;
	mlx_key_hook(mlx, &ft_hook_movement, game);
	//mlx_loop_hook(mlx, &move_enemy, game);
	mlx_loop(mlx);
	return (1);
}


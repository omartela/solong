/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartela <omartela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 08:54:44 by omartela          #+#    #+#             */
/*   Updated: 2024/07/18 08:54:47 by omartela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long_bonus.h"

void	init_game_variables(t_game *game)
{
	game->players = 0;
	game->exits = 0;
	game->collectibles = 0;
	game->enemies = 0;
	game->move_count = 0;
	game->score = 0;
}

int	init_map(t_game *game)
{
	if (!read_map(game))
		return (0);
	if (!validate_map(game))
	{
		free_map(game->map, game->map_height);
		return (0);
	}
	return (1);
}

int	check_width(t_game *game)
{
	int	width;

	width = game->map_width * TILE_SIZE + TILE_SIZE;
	if (width < 300)
	{
		return (300);
	}
	return (width);
}

int	init_game(t_game *game)
{
	mlx_t		*mlx;
	t_list		*llist;
	int			width;
	int			height;

	llist = NULL;
	init_game_variables(game);
	if (!init_map(game))
		return (0);
	width = check_width(game);
	height = game->map_height * TILE_SIZE + TILE_SIZE;
	mlx = mlx_init(width, height, "Dwarf & Diamonds", true);
	if (!mlx)
		error("Failed to initialize mlx");
	game->mlx = mlx;
	mlx_set_setting(MLX_STRETCH_IMAGE,1);
	init_game_images(game, &llist);
	extract_map_data(game, &llist);
	game->llist = llist;
	mlx_key_hook(mlx, &ft_hook_movement, game);
	mlx_loop(mlx);
	mlx_terminate(game->mlx);
	return (1);
}

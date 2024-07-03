/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartela <omartela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 23:25:34 by omartela          #+#    #+#             */
/*   Updated: 2024/07/03 10:04:06 by omartela         ###   ########.fr       */
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

int	check_map_size(int width, int height)
{
	int	m_width;
	int	m_height;

	m_width = width;
	m_height = height;
	mlx_get_monitor_size(0, &m_width, &m_height);
	if (width > m_width || height > m_height)
	{
		error("Map size too big. It is larger than monitor size");
		return (0);
	}
	return (1);
}

int	init_mlx(t_game *game, int width, int height)
{
	mlx_t	*mlx;

	mlx = mlx_init(width, height, "Dwarf & Diamonds", true);
	if (!mlx)
	{
		free_map(game->map, game->map_height);
		error("Failed to initialize mlx");
		return (0);
	}
	if (!check_map_size(width, height))
	{
		free_map(game->map, game->map_height);
		return (0);
	}
	game->mlx = mlx;
	return (1);
}

int	init_game(t_game *game)
{
	t_list		*llist;
	int			width;
	int			height;

	llist = NULL;
	init_game_variables(game);
	if (!init_map(game))
		return (0);
	width = game->map_width * T_SIZE;
	if (width < 300)
		width 300
	height = game->map_height * T_SIZE;
	if (!init_mlx(game, width, height))
		return (0);
	mlx_set_setting(MLX_STRETCH_IMAGE, 1);
	if (!init_game_images(game, &llist))
		return (0);
	extract_map_data(game, &llist);
	game->llist = llist;
	return (1);
}

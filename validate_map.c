/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartela <omartela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:03:58 by omartela          #+#    #+#             */
/*   Updated: 2024/07/02 14:11:43 by omartela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

static int	validate_walls_sides(t_game *game)
{
	size_t	h;

	h = 0;
	while (h < game->map_height)
	{
		if (game->map[h][0] != '1')
		{
			error(WALLS_SIDES);
			return (0);
		}
		++h;
	}
	h = 0;
	while (h < game->map_height)
	{
		if (game->map[h][game->map_width - 1] != '1')
		{
			error(WALLS_SIDES);
			return (0);
		}
		++h;
	}
	return (1);
}

static int	validate_walls_top_bot(t_game *game)
{
	size_t	w;

	w = 0;
	while (w < game->map_width)
	{
		if (game->map[0][w] != '1')
		{
			error(WALLS_TOP_BOT);
			return (0);
		}
		++w;
	}
	w = 0;
	while (w < game->map_width)
	{
		if (game->map[game->map_height - 1][w] != '1')
		{
			error(WALLS_TOP_BOT);
			return (0);
		}
		++w;
	}
	return (1);
}

static size_t	calc_map_row_len(t_game *game, size_t i)
{
	size_t	len;

	len = 0;
	if (ft_strrchr(game->map[i], '\n'))
	{
		while (game->map[i][len] != '\n')
			++len;
	}
	else
	{
		len = ft_strlen(game->map[i]);
	}
	return (len);
}

static int	validate_rectangle(t_game *game)
{
	size_t	h;
	size_t	len;

	h = 0;
	len = calc_map_row_len(game, 0);
	while (h < game->map_height - 1)
	{
		if (len != calc_map_row_len(game, h))
		{
			error(WALLS_RECTANGLE);
			return (0);
		}
		++h;
	}
	return (1);
}

int	validate_map(t_game *game)
{
	if (!validate_rectangle(game))
		return (0);
	if (!validate_walls_sides(game))
		return (0);
	if (!validate_walls_top_bot(game))
		return (0);
	if (!validate_map_chars_and_ext(game))
		return (0);
	if (!start_bfs(game))
	{
		error("Not valid map bfs failed\n");
		return (0);
	}
	return (1);
}

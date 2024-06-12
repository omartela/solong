/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartela <omartela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:03:58 by omartela          #+#    #+#             */
/*   Updated: 2024/06/12 15:32:14 by omartela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

static int	validate_walls_sides(t_game *game)
{
	size_t	h;

	h = 0;
	while (h < game->map_height)
	{
		if (game->map[0][h] != '1')
			return (0);
		++h;
	}
	h = 0;
	while (h < game->map_height)
	{
		if (game->map[game->map_width - 1][h])
			return (0);
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
			return (0);
		++w;
	}
	w = 0;
	while (w < game->map_width)
	{
		if (game->map[game->map_height - 1][w] != '1')
			return (0);
		++w;
	}
	return (1);
}

static int	validate_rectangle(t_game *game)
{
	size_t	h;
	size_t	w;
	size_t	len;

	h = 0;
	len = ft_strlen(game->map[0]);
	while (h < game->map_height)
	{
		if (len != (ft_strlen(game->map[h])))
			return (0);
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
	if (!start_bfs(game->map, game->map_height))
		return (0);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_2_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartela <omartela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 08:58:50 by omartela          #+#    #+#             */
/*   Updated: 2024/07/18 14:45:06 by omartela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long_bonus.h"

static int	validate_file_ext(char *file)
{
	char	*ext;

	ext = NULL;
	ext = ft_strrchr(file, '.');
	if (ext == NULL)
	{
		error("Invalid file name or extension");
		return (0);
	}
	if (ft_strncmp(ext, ".ber\0", 5) != 0)
	{
		error("Invalid file name or extension");
		return (0);
	}
	return (1);
}

static void	check_character(t_game *game, int c)
{
	if (c == 'E')
		game->exits += 1;
	else if (c == 'P')
		game->players += 1;
	else if (c == 'C')
		game->collectibles += 1;
	else if (c == '!')
		game->enemies += 1;
}

static int	validate_map_char(char c)
{
	if (ft_strchr("PC1!E0", c))
		return (1);
	return (0);
}

static int	validate_map_chars(t_game *game)
{
	size_t	h;
	size_t	w;

	h = 0;
	while (h < game->map_height)
	{
		w = 0;
		while (w < game->map_width)
		{
			if (!validate_map_char(game->map[h][w]))
			{
				error(MAP_CHARS);
				return (0);
			}
			check_character(game, game->map[h][w]);
			++w;
		}
		++h;
	}
	if (game->collectibles < 1 || game->players != 1 || game->exits != 1)
	{
		error("Too few or too many players, enemies, collectibles or exits");
		return (0);
	}
	return (1);
}

int	validate_map_chars_and_ext(t_game *game)
{
	if (!validate_file_ext(game->filename))
		return (0);
	if (!validate_map_chars(game))
		return (0);
	if (game->enemies != 1)
	{
		error("Too few or too many players, enemies, collectibles or exits");
		return (0);
	}
	return (1);
}

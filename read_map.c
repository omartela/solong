/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartela <omartela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 14:34:42 by omartela          #+#    #+#             */
/*   Updated: 2024/06/13 19:45:16 by omartela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

void	extract_map_data(t_game *game, t_list **llist)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (game->map[y][x] == 'P')
				insert_image_to_window((*llist)->content, x * TILE_SIZE, y * TILE_SIZE + TILE_SIZE);
			if (game->map[y][x] == 'C')
				insert_image_to_window((*llist)->next->content, x * TILE_SIZE, y * TILE_SIZE + TILE_SIZE);
			if (game->map[y][x] == '1')
				insert_image_to_window((*llist)->next->next->content, x * TILE_SIZE, y * TILE_SIZE + TILE_SIZE);
			if (game->map[y][x] == 'E')
				insert_image_to_window((*llist)->next->next->next->content, x * TILE_SIZE, y * TILE_SIZE + TILE_SIZE);
			//if (game->map[y][x] == '0')
				//insert_image_to_window((*llist)->next->next->next->next->content, x * TILE_SIZE, y * TILE_SIZE);
			++x;
		}
		++y;
	}
}

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;
	size_t	copy_size;

	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);
	if (old_size < new_size)
	{
		copy_size = old_size;
	}
	else
	{
		copy_size = new_size;
	}
	if (ptr)
	{
		ft_memcpy(new_ptr, ptr, copy_size);
		free(ptr);
	}
	return (new_ptr);
}

void	free_map(char **map, size_t i)
{
	while (i > 0)
	{
		i--;
		free(map[i]);
	}
	free(map);
}

void	read_map(t_game *game)
{
	int		fd;
	char	**map;
	size_t	ln;
	char	*line;

	fd = open(game->filename, O_RDONLY);
	if (fd == -1)
		return ;
	line = get_next_line(fd);
	if (!line)
	{
		close(fd);
		return ;
	}
	map = malloc(1 * sizeof(char *));
	if (!map)
	{
		close(fd);
		return ;
	}
	map[0] = line;
	ln = 1;
	while (line != NULL)
	{
		line = get_next_line(fd);
		map = ft_realloc(map, ln * sizeof(char *), (ln + 1) * sizeof(char *));
		if (!map)
		{
			free_map(map, ln);
			free(line);
			close(fd);
			return ;
		}
		map[ln] = line;
		if (line)
			++ln;
	}
	/// index start from 0 so that is why (line numbers)ln - 1
	game->map_height = ln;
	/// Every line has /0 character so thats why -1 so dont take that into account.
	game->map_width = ft_strlen(map[0]) - 1;
	game->map = map;
	close(fd);
}

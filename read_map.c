/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartela <omartela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:34:42 by omartela          #+#    #+#             */
/*   Updated: 2024/06/10 14:00:07 by omartela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"
#include "stdio.h"
// error handling for the map
// implement check that in the map there is no symbols which are not allowed.
// implement check that player cant reach collectable or door
// 

void	extract_map_data(char *line, t_list **llist, int y)
{
	int		x;

	x = 0;
	while (line[x])
	{
		if (line[x] == 'P')
		{
			insert_image_to_window((*llist)->content, x * TILE_SIZE, y * TILE_SIZE);
		}
		else if (line[x] == 'C')
		{
			insert_image_to_window((*llist)->next->content, x * TILE_SIZE, y * TILE_SIZE);
		}
		else if (line[x] == '1')
		{
			insert_image_to_window((*llist)->next->next->content, x * TILE_SIZE, y * TILE_SIZE);
		}
		else if (line[x] == 'E')
		{
			insert_image_to_window((*llist)->next->next->next->content, x * TILE_SIZE, y * TILE_SIZE);
		}
		else if (line[x] == '0')
		{
			insert_image_to_window((*llist)->next->next->next->next->content, x * TILE_SIZE, y * TILE_SIZE);
		}
		++x;
	}
}

int	validate_map_char(char c)
{
	if (ft_strchr("PC1E0", c))
	{
		return (1);
	}
	else
	{
		return (0);
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

void	read_map(char *file, t_list **llist)
{
	int		fd;
	char	**map;
	int		lines_read;
	char	*line;

	fd = open(file, O_RDONLY);
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
	lines_read = 1;
	while (line != NULL)
	{
		extract_map_data(line, llist, lines_read - 1);
		line = get_next_line(fd);
		map = ft_realloc(map, lines_read * sizeof(char *), (lines_read + 1) * sizeof(char *));
		if (!map)
		{
			free(line);
			close(fd);
			return ;
		}
		map[lines_read] = line;
		++lines_read;
	}
	close(fd);
}

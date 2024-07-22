/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartela <omartela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 08:57:54 by omartela          #+#    #+#             */
/*   Updated: 2024/07/18 08:57:56 by omartela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long_bonus.h"

static void	add_image_to_window(void *content, int x, int y)
{
	insert_image_to_window(content, x * T_SIZE, y * T_SIZE + T_SIZE);
}

void	extract_map_data(t_game *game, t_list **llist)
{
	size_t	x;
	size_t	y;
	void	*enemy;

	y = 0;
	enemy = (*llist)->next->next->next->next->content;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (game->map[y][x] == 'P')
				add_image_to_window((*llist)->content, x, y);
			if (game->map[y][x] == 'C')
				add_image_to_window((*llist)->next->content, x, y);
			if (game->map[y][x] == '1')
				add_image_to_window((*llist)->next->next->content, x, y);
			if (game->map[y][x] == 'E')
				add_image_to_window((*llist)->next->next->next->content, x, y);
			if (game->map[y][x] == '!')
				add_image_to_window(enemy, x, y);
			++x;
		}
		++y;
	}
}

static int	check_empty_file(int fd, char **line)
{
	*line = get_next_line(fd);
	if (!(*line))
	{
		error("Read failed or empty file");
		return (0);
	}
	return (1);
}

static int	read_lines(int fd, char ***map, t_game *game)
{
	char	*line;
	int		ln;

	line = NULL;
	if (!check_empty_file(fd, &line))
		return (0);
	(*map)[0] = line;
	ln = 1;
	while (line != NULL)
	{
		line = get_next_line(fd);
		*map = ft_realloc(*map, ln * sizeof(char *), (ln + 1) * sizeof(char *));
		if (!*map)
		{
			free_map(*map, ln);
			free(line);
			line = NULL;
			return (0);
		}
		(*map)[ln] = line;
		if (line)
			++ln;
	}
	game->map_height = ln;
	return (1);
}

int	read_map(t_game *game)
{
	int		fd;
	char	**map;

	fd = open(game->filename, O_RDONLY);
	if (fd == -1)
	{
		error("File could not be opened");
		return (0);
	}
	map = malloc(1 * sizeof(char *));
	if (!map)
	{
		close(fd);
		return (0);
	}
	if (!read_lines(fd, &map, game))
	{
		close(fd);
		return (0);
	}
	game->map_width = ft_strlen(map[0]) - 1;
	game->map = map;
	close(fd);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartela <omartela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:34:42 by omartela          #+#    #+#             */
/*   Updated: 2024/06/05 20:14:14 by omartela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

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
			insert_image_to_window((*llist)->content, x * 40, y * 40);
		}
		else if (line[x] == 'C')
		{
			insert_image_to_window((*llist)->next->content, x * 40, y * 40);
		}
		else if (line[x] == '1')
		{
			insert_image_to_window((*llist)->next->next->content, x * 40, y * 40);
		}
		//else if (line[x] == 'E')
		//{
			//insert_image_to_window((*llist)->next->next->next->content, x * 10, y * 10);
		//}
		++x;
	}
}

void	read_map(char *file, t_list **llist)
{
	int		fd;
	char	*line;
	int		y;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return ;
	line = get_next_line(fd);
	y = 0;
	while (line != NULL)
	{
		extract_map_data(line, llist, y);
		line = get_next_line(fd);
		++y;
	}
	close(fd);
}

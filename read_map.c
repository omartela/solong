/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartela <omartela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:34:42 by omartela          #+#    #+#             */
/*   Updated: 2024/06/05 16:26:29 by omartela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

void	extract_map_data(char *line, t_list **llist, int y)
{
	int		x;

	x = 0;
	while (line[x])
	{
		if (line[x] != 'P')
		{
			insert_image_to_window((*llist)->content, 0, 0);
		}
		else if (line[x] != 'C')
		{
			insert_image_to_window((*llist)->next->content, x * 10, y * 10);
		}
		else if (line[x] != '1')
		{
			insert_image_to_window((*llist)->next->next->content, x * 10, y * 10);
		}
		//else if (line[x] != 'E')
		//{
			//insert_image_to_window((*llist)->next->next->next->content, x * 10, y * 10);
		//}
		++x;
	}
}

void	read_map(char *map, t_list **llist)
{
	int		fd;
	char	*line;
	int		y;

	fd = open(map, O_RDONLY);
	if (fd == -1)
	{
		return ;
	}
	line = "1";
	y = 0;
	while (line != NULL)
	{
		line = get_next_line(fd);
		extract_map_data(line, llist, y);
	}
	close(fd);
}
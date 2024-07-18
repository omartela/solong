/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartela <omartela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 08:53:04 by omartela          #+#    #+#             */
/*   Updated: 2024/07/18 13:55:32 by omartela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long_bonus.h"

int	check_collision(mlx_image_t *obstacle, mlx_image_t *p, int i, int movement_x, int movement_y)
{
	unsigned int	x1;
	unsigned int	y1;
	unsigned int	x2;
	unsigned int	y2;

	x1 = (unsigned int)obstacle->instances[i].x;
	x2 = (unsigned int)p->instances[0].x + movement_x;
	y1 = (unsigned int)obstacle->instances[i].y;
	y2 = (unsigned int)p->instances[0].y + movement_y;
	if (obstacle->instances[i].enabled == false)
		return (0);
	if (x1 < x2 + p->width && x1 + obstacle->width > x2 && y1 < y2 + p->height
		&& y1 + obstacle->height > y2)
		return (1);
	return (0);
}

int	check_collision_to_player(void *content, t_img *p)
{
	t_img	*obs;

	obs = (t_img *)content;
	if (check_collision(obs->image, p->image, 0, 0, 0))
		return (1);
	return (0);
}

int	check_obstacle(void *obc, t_img *p, int movement, char direction)
{
	t_img	*obstacle;
	size_t	i;

	obstacle = (t_img *)obc;
	i = 0;
	while (i < obstacle->image->count)
	{
		if (direction == 'x')
			if (check_collision(obstacle->image, p->image, i, movement, 0))
				return (1);
		if (direction == 'y')
			if (check_collision(obstacle->image, p->image, i, 0, movement))
				return (1);
		++i;
	}
	return (0);
}

int	check_collectable(void *content, t_img *p)
{
	t_img	*collectable;
	size_t	i;

	i = 0;
	collectable = (t_img *)content;
	while (i < collectable->image->count)
	{
		if (check_collision(collectable->image, p->image, i, 0, 0))
		{
			collectable->image->instances[i].enabled = false;
			return (1);
		}
		++i;
	}
	return (0);
}

int	check_exit(t_game *game, t_img *p)
{
	if (check_collision_to_player(game->llist->next->next->next->content, p))
	{
		if (game->score == game->collectibles)
			return (1);
	}
	return (0);
}

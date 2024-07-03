/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartela <omartela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 14:26:43 by omartela          #+#    #+#             */
/*   Updated: 2024/06/28 12:30:59 by omartela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

int	check_collision(mlx_image_t *obs, mlx_image_t *p, int i, t_movement mv)
{
	unsigned int	x1;
	unsigned int	y1;
	unsigned int	x2;
	unsigned int	y2;

	x1 = (unsigned int)obs->instances[i].x;
	x2 = (unsigned int)p->instances[0].x + mv.x;
	y1 = (unsigned int)obs->instances[i].y;
	y2 = (unsigned int)p->instances[0].y + mv.y;
	if (obs->instances[i].enabled == false)
		return (0);
	if (x1 < x2 + p->width && x1 + obs->width > x2 && y1 < y2 + p->height
		&& y1 + obs->height > y2)
		return (1);
	return (0);
}

int	check_collision_to_player(void *content, t_img *p)
{
	t_img		*obs;
	t_movement	mv;

	mv.x = 0;
	mv.y = 0;
	obs = (t_img *)content;
	if (check_collision(obs->image, p->image, 0, mv))
		return (1);
	return (0);
}

int	check_obstacle(void *obc, t_img *p, int movement, char direction)
{
	t_img		*obstacle;
	size_t		i;
	t_movement	mv;

	obstacle = (t_img *)obc;
	i = 0;
	mv.x = 0;
	mv.y = 0;
	while (i < obstacle->image->count)
	{
		if (direction == 'x')
			mv.x += movement;
		if (direction == 'y')
			mv.y += movement;
		if (check_collision(obstacle->image, p->image, i, mv))
			return (1);
		++i;
		mv.x = 0;
		mv.y = 0;
	}
	return (0);
}

int	check_collectable(void *content, t_img *p)
{
	t_img		*collectable;
	size_t		i;
	t_movement	mv;

	i = 0;
	mv.x = 0;
	mv.y = 0;
	collectable = (t_img *)content;
	while (i < collectable->image->count)
	{
		if (check_collision(collectable->image, p->image, i, mv))
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
		else
			ft_putstr_fd("You need to collect all the diamonds first \n", 1);
	}
	return (0);
}

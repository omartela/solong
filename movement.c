/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartela <omartela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 14:25:10 by omartela          #+#    #+#             */
/*   Updated: 2024/06/17 14:25:12 by omartela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

void	ft_hook_movement(mlx_key_data_t keydata, void *param)
{
	mlx_t	*mlx;
	t_img	*params;
	t_list	*llist;

	llist = (t_list *)param;
	params = (t_img *)llist->content;
	mlx = params->mlx;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(mlx);
	if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
	{
		if (!check_obstacle(llist->next->next->content, params, -TILE_SIZE, 'y'))
		{
			params->image->instances[0].y -= TILE_SIZE;
			check_collectable(llist->next->content, params);
			check_exit(llist->next->next->next->content, params);
		}
	}
	if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS)
	{
		if (!check_obstacle(llist->next->next->content, params, TILE_SIZE, 'y'))
		{
			params->image->instances[0].y += TILE_SIZE;
			check_collectable(llist->next->content, params);
			check_exit(llist->next->next->next->content, params);
		}
	}
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
	{
		if (!check_obstacle(llist->next->next->content, params, -TILE_SIZE, 'x'))
		{
			params->image->instances[0].x -= TILE_SIZE;
			check_collectable(llist->next->content, params);
			check_exit(llist->next->next->next->content, params);
		}
	}
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
	{
		if (!check_obstacle(llist->next->next->content, params, TILE_SIZE, 'x'))
		{
			params->image->instances[0].x += TILE_SIZE;
			check_collectable(llist->next->content, params);
			check_exit(llist->next->next->next->content, params);
		}
	}
}
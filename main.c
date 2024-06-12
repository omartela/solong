/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartela <omartela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 10:05:25 by omartela          #+#    #+#             */
/*   Updated: 2024/06/07 15:47:46 by omartela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"
#include <stdio.h>
int	check_collision(mlx_image_t *obstacle, mlx_image_t *p, int i)
{
	unsigned int	x1;
	unsigned int	y1;
	unsigned int	x2;
	unsigned int	y2;

	x1 = (unsigned int)obstacle->instances[i].x;
	x2 = (unsigned int)p->instances[0].x;
	y1 = (unsigned int)obstacle->instances[i].y;
	y2 = (unsigned int)p->instances[0].y;
	if (x1 < x2 + p->width && x1 + obstacle->width > x2 && y1 < y2 + p->height &&
		y1 + obstacle->height > y2)
	{
		return (1);
	}
	return (0);
}

int	check_movement_collision_y(mlx_image_t *obstacle, mlx_image_t *p, int i, int movement)
{
	unsigned int	x1;
	unsigned int	x2;
	unsigned int	y1;
	unsigned int	y2;

	x1 = (unsigned int)obstacle->instances[i].x;
	x2 = (unsigned int)p->instances[0].x;
	y1 = (unsigned int)obstacle->instances[i].y;
	y2 = (unsigned int)p->instances[0].y + movement;
	if (x1 < x2 + p->width && x1 + obstacle->width > x2 && y1 < y2 + p->height &&
		y1 + obstacle->height > y2)
	{
		return (1);
	}
	return (0);
}

int	check_movement_collision_x(mlx_image_t *obstacle, mlx_image_t *p, int i, int movement)
{
	unsigned int	x1;
	unsigned int	x2;
	unsigned int	y1;
	unsigned int	y2;

	x1 = (unsigned int)obstacle->instances[i].x;
	x2 = (unsigned int)p->instances[0].x + movement;
	y1 = (unsigned int)obstacle->instances[i].y;
	y2 = (unsigned int)p->instances[0].y;
	if (x1 < x2 + p->width && x1 + obstacle->width > x2 && y1 < y2 + p->height &&
		y1 + obstacle->height > y2)
	{
		return (1);
	}
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
			if (check_movement_collision_x(obstacle->image, p->image, i, movement))
				return (1);
		if (direction == 'y')
			if (check_movement_collision_y(obstacle->image, p->image, i, movement))
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
		if (check_collision(collectable->image, p->image, i))
		{
			collectable->image->instances[i].enabled = false;
			return (1);
		}
		++i;
	}
	return (0);
}

int	check_exit(void *content, t_img *p)
{
	t_img	*collectable;

	collectable = (t_img *)content;
	if (check_collision(collectable->image, p->image, 0))
	{
		mlx_close_window(collectable->mlx);
		return (1);
	}
	return (0);
}

void	ft_hook(mlx_key_data_t keydata, void *param)
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

void	resize_image(void *content, unsigned int x, unsigned int y)
{
	t_img	*img;

	img = (t_img *)content;
	mlx_resize_image(img->image, x, y);
}

void	insert_image_to_window(void *content, int x, int y)
{
	t_img	*img;

	img = (t_img *)content;
	mlx_image_to_window(img->mlx, img->image, x, y);
}

void	set_image_position(t_img *img, int pos_x, int pos_y)
{
	img->image->instances[1].x = pos_x;
	img->image->instances[1].y = pos_y;
}

int	main(int argc, char *argv[])
{
	mlx_t		*mlx;
	t_list		*llist;
	//char		**game;

	llist = NULL;
	if (argc)
		argc = 3;
	mlx = mlx_init(480, 480, "Dwarf & Diamonds", true);
	if (!mlx)
		error();
	load_images_to_struct(&llist, "DwarfSprite1.png", mlx);
	load_images_to_struct(&llist, "amethyst.png", mlx);
	load_images_to_struct(&llist, "Rock Pile 1 - AZURE - small.PNG", mlx);
	load_images_to_struct(&llist, "Door02.png", mlx);
	resize_image(llist->content, TILE_SIZE, TILE_SIZE);
	resize_image(llist->next->content, TILE_SIZE, TILE_SIZE);
	resize_image(llist->next->next->content, TILE_SIZE, TILE_SIZE);
	resize_image(llist->next->next->next->content, TILE_SIZE, TILE_SIZE);
	//insert_image_to_window(llist->next->next->content);
	//set_image_position(llist->next->next->content, 100, 100);
	//ft_lstiter(llist, &insert_image_to_window);
	read_map(argv[1], &llist);
	mlx_key_hook(mlx, &ft_hook, llist);
	mlx_loop(mlx);
	//mlx_delete_image(mlx, i_s1.image);
	//mlx_delete_image(mlx, i_s2.image);
	//mlx_delete_texture(texture);
    // Optional, terminate will clean up any leftover images (not textures!)
	ft_lstclear(&llist, &delete_img_node);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}

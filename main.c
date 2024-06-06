??? from here until ???END lines may have been inserted/deleted
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartela <omartela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 12:46:18 by omartela          #+#    #+#             */
/*   Updated: 2024/06/05 23:17:41 by omartela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

int check_collision(mlx_image_t *img1, mlx_image_t *img2, int i)
{
    if ((unsigned int)img1->instances[i].x < (unsigned int)img2->instances[i].x + img2->width &&
        (unsigned int)img1->instances[i].x + img1->width > (unsigned int)img2->instances[i].x &&
        (unsigned int)img1->instances[i].y < (unsigned int)img2->instances[i].y + img2->height &&
        (unsigned int)(img1->instances[i].y + img1->height) > (unsigned int)img2->instances[i].y)
	{
		return 1;
	}
	return 0;
}

int check_movement_collision_y(mlx_image_t *img1, mlx_image_t *img2, int i, int movement)
{
	int new_y;

    new_y = img1->instances[i].y - movement;
    if ((unsigned int)img1->instances[i].x < (unsigned int)img2->instances[i].x + img2->width &&
        (unsigned int)(img1->instances[i].x + img1->width) > (unsigned int)img2->instances[i].x &&
        (unsigned int)new_y < (unsigned int)img2->instances[i].y + img2->height &&
        (unsigned int)new_y + img1->height > (unsigned int)img2->instances[i].y)
	{
        return 1;
	}

    return 0;
}


int check_movement_collision_x(mlx_image_t *img1, mlx_image_t *img2, int i, int movement)
{
	int new_x;

    new_x = img1->instances[i].x - movement;
    if ((unsigned int)new_x < (unsigned int)img2->instances[i].x + img2->width &&
        (unsigned int)new_x + img1->width > (unsigned int)img2->instances[i].x &&
        (unsigned int)img1->instances[i].y < (unsigned int)img2->instances[i].y + img2->height &&
        (unsigned int)(img1->instances[i].y + img1->height) > (unsigned int)img2->instances[i].y)
    {
        return 1;
    }
    return 0;
}


int check_obstacle(void *obstacle, t_img *p, int movement)
{
	t_img	*obstacle;
	int		i;

	obstacle = (t_img *)obstacle;
	while (i < obstacle->image.count)
	{
		if (check_movement_collision_x(obstacle, p, i, movement))
			return (1);
	}
}

int check_collectable(void *content, t_img *p)
{
	t_img	*collectable;
	int		i;

	i = 0;
	collectable = (t_img *)content;
	while (i < collectable->image.count)
	{
		if (check_collision(collectable, p, i))
			return (1);
		++i;
	}
	return (0);
}

void	ft_hook(void *param)
{
	mlx_t	*mlx;
	t_img	*params;
	t_list	*llist;

	llist = (t_list *)param;
	params = (t_img *)llist->content;
	mlx = params->mlx;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
	{
		if (check_obstacle(llist->next->next->content, 1))
		{
			params->image->instances[0].y -= 1;
			check_collectable(llist->next->content, params);
		}
	}
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
	{
		if (check_obstacle(llist->next->next->content, 1)
		{
			params->image->instances[0].y += 1;
			check_collectable(llist->next->content, params);
		}
	}
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		params->image->instances[0].x -= 1;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		params->image->instances[0].x += 1;
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

int	main(void)
{
	mlx_t		*mlx;
	t_list		*llist;

	llist = NULL;
	mlx = mlx_init(500, 500, "Dwarf & Diamonds", true);
	if (!mlx)
		error();
	load_images_to_struct(&llist, "DwarfSprite1.png", mlx);
	load_images_to_struct(&llist, "golddiamond.png", mlx);
	load_images_to_struct(&llist, "Rock Pile 1 - AZURE - small.PNG", mlx);
	//insert_image_to_window(llist->next->next->content);
	//set_image_position(llist->next->next->content, 100, 100);
	//ft_lstiter(llist, &insert_image_to_window);
	read_map("testmap.ber", &llist);
	mlx_loop_hook(mlx, ft_hook, llist);
	mlx_loop(mlx);
	//mlx_delete_image(mlx, i_s1.image);
	//mlx_delete_image(mlx, i_s2.image);
	//mlx_delete_texture(texture);
    // Optional, terminate will clean up any leftover images (not textures!)
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}

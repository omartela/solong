/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartela <omartela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 12:46:18 by omartela          #+#    #+#             */
/*   Updated: 2024/06/03 14:48:15 by omartela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
int	check_collision(mlx_image_t *img1, mlx_image_t *img2)
{
	if (img1->instances[0].x < img2->instances[0].x + img2->width
			&& img1->instances[0].x + img1->width > img2->instances[0].x)
		return (1);
	if (img1->instances[0].y < img2->instances[0].y + img2->height
			&& img1->instances[0].y + img1->height > img2->instances[0].y)
		return (1);
	return (0);
}
*/
void	ft_hook(void *param)
{
	mlx_t	*mlx;
	t_img	*params;

	params = (t_img *)param;
	mlx = params->mlx;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		params->image->instances[0].y -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		params->image->instances[0].y += 5;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		params->image->instances[0].x -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		params->image->instances[0].x += 5;
}

void	insert_image_to_window(void *content)
{
	t_img	*img;

	img = (t_img *)content;
	mlx_image_to_window(img->mlx, img->image, 0, 0);
}

void	set_image_position(t_img *img, int n_instance, int pos_x, int pos_y)
{
	img->image->instances[n_instance].x = pos_x;
	img->image->instances[n_instance].y = pos_y;
}

int	main(void)
{
	mlx_t		*mlx;
	t_list		*llist;

	llist = NULL;
	mlx = mlx_init(512, 512, "Test", true);
	if (!mlx)
		error();
	load_images_to_struct(&llist, "DwarfSprite1.png", mlx);
	load_images_to_struct(&llist, "golddiamond.png", mlx);
	load_images_to_struct(&llist, "Rock1.png", mlx);
	insert_image_to_window(llist->next->next->content);
	set_image_position(llist->next->next->content, 1, 100, 100);	
	ft_lstiter(llist, &insert_image_to_window);
	mlx_loop_hook(mlx, ft_hook, llist->content);
	mlx_loop(mlx);
	//mlx_delete_image(mlx, i_s1.image);
	//mlx_delete_image(mlx, i_s2.image);
	//mlx_delete_texture(texture);
    // Optional, terminate will clean up any leftover images (not textures!)
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}

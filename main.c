/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartela <omartela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 12:46:18 by omartela          #+#    #+#             */
/*   Updated: 2024/05/31 15:33:52 by omartela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

typedef	struct s_img
{
	mlx_t *mlx;
	mlx_image_t *image;
	mlx_texture_t *texture;
} img_t;

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
	img_t	*params;

	params = (img_t *)param;
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

static void	error(void)
{
	puts(mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

void	load_texture(char *str, img_t *i_s)
{
	mlx_texture_t	*texture;

	texture = mlx_load_png(str);
	if (!texture)
		error();
	i_s->texture = texture;
}

void	load_image(char *str, mlx_t *mlx, img_t *i_s)
{
	mlx_image_t		*img;

	load_texture(str, i_s);
	img = mlx_texture_to_image(mlx, i_s->texture);
	if (!img)
		error();
	i_s->image = img;
}

void	insert_image_to_window(mlx_t *mlx, mlx_image_t *img)
{
	if (mlx_image_to_window(mlx, img, 0, 0) < 0)
		error();
}

int32_t	main(void)
{
	mlx_t		*mlx;
	img_t i_s1;
	img_t i_s2;

	mlx = mlx_init(512, 512, "Test", true);
	if (!mlx)
		error();
	i_s1.mlx = mlx;
	i_s2.mlx = mlx;
	load_image("DwarfSprite1.png", mlx, &i_s1);
	load_image("golddiamond.png", mlx, &i_s2);
	insert_image_to_window(mlx, i_s1.image);
	insert_image_to_window(mlx, i_s2.image);
	i_s2.image->instances[0].y += 200;
	i_s2.image->instances[0].x += 200;
	mlx_loop_hook(mlx, ft_hook, &i_s1);
	mlx_loop(mlx);
	mlx_delete_image(mlx, i_s1.image);
	mlx_delete_image(mlx, i_s2.image);
	//mlx_delete_texture(texture);
    // Optional, terminate will clean up any leftover images (not textures!)
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}

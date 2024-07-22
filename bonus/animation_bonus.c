/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartela <omartela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 08:50:03 by omartela          #+#    #+#             */
/*   Updated: 2024/07/18 08:50:08 by omartela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long_bonus.h"

static int	animate_right_dir(t_img *img, char direction)
{
	if (direction == 'r')
	{
		if (img->previous_dir != direction)
		{
			if (!load_image(img->r_idle_images[0], img->mlx, img))
				return (0);
			img->ri = 0;
		}
		else if (img->ri == img->last_ri_index)
		{
			if (!load_image(img->r_idle_images[0], img->mlx, img))
				return (0);
			img->ri = 0;
		}
		else
		{
			if (!load_image(img->right_images[img->ri], img->mlx, img))
				return (0);
			img->ri += 1;
		}
		img->previous_dir = 'r';
	}
	return (1);
}

static int	animate_left_dir(t_img *img, char direction)
{
	if (direction == 'l')
	{
		if (img->previous_dir != direction)
		{
			if (!load_image(img->l_idle_images[0], img->mlx, img))
				return (0);
			img->li = 0;
		}
		else if (img->li == img->last_li_index)
		{
			if (!load_image(img->l_idle_images[0], img->mlx, img))
				return (0);
			img->li = 0;
		}
		else
		{
			if (!load_image(img->left_images[img->li], img->mlx, img))
				return (0);
			img->li += 1;
		}
		img->previous_dir = 'l';
	}
	return (1);
}

int	animation(char direction, void *content)
{
	mlx_image_t	*mlx_image;
	t_img		*img;
	int			x;
	int			y;

	img = (t_img *)content;
	mlx_image = img->image;
	x = mlx_image->instances[0].x;
	y = mlx_image->instances[0].y;
	if (!animate_right_dir(img, direction) || !animate_left_dir(img, direction))
	{
		error("Animation failed to load image");
		return (0);
	}
	resize_image(content, T_SIZE, T_SIZE);
	insert_image_to_window(content, x, y);
	mlx_delete_image(img->mlx, mlx_image);
	return (1);
}

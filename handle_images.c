/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_images.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartela <omartela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 14:44:52 by omartela          #+#    #+#             */
/*   Updated: 2024/06/27 14:50:59 by omartela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

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

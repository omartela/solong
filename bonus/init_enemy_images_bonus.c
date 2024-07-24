/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_enemy_images_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartela <omartela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 11:22:23 by omartela          #+#    #+#             */
/*   Updated: 2024/07/24 11:28:12 by omartela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long_bonus.h"

static void	set_enemy_right_images(t_img *img)
{
	img->right_images[0] = "png/goblinright-1.png";
	img->right_images[1] = "png/goblinright-2.png";
	img->right_images[2] = "png/goblinright-3.png";
	img->right_images[3] = "png/goblinright-4.png";
	img->right_images[4] = "png/goblinright-5.png";
	img->right_images[5] = "png/goblinright-6.png";
	img->right_images[6] = "png/goblinright-7.png";
	img->right_images[7] = "png/goblinright-8.png";
	img->right_images[8] = "png/goblinright-9.png";
}

static void	set_enemy_left_images(t_img *img)
{
	img->left_images[0] = "png/goblinleft-1.png";
	img->left_images[1] = "png/goblinleft-2.png";
	img->left_images[2] = "png/goblinleft-3.png";
	img->left_images[3] = "png/goblinleft-4.png";
	img->left_images[4] = "png/goblinleft-5.png";
	img->left_images[5] = "png/goblinleft-6.png";
	img->left_images[6] = "png/goblinleft-7.png";
	img->left_images[7] = "png/goblinleft-8.png";
	img->left_images[8] = "png/goblinleft-9.png";
}

int	init_enemy_images(t_game *game, t_list **llist)
{
	t_img	*img;

	if (!load_image_to_struct(llist, "png/goblinright-1.png", game->mlx))
		return (0);
	img = (t_img *)(*llist)->next->next->next->next->content;
	set_enemy_right_images(img);
	set_enemy_left_images(img);
	img->r_idle_images[0] = "png/goblinright-1.png";
	img->l_idle_images[0] = "png/goblinleft-1.png";
	init_image_indexes(img, 8, 8);
	return (1);
}

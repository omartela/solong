/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player_images_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartela <omartela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 11:28:35 by omartela          #+#    #+#             */
/*   Updated: 2024/07/24 11:35:24 by omartela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long_bonus.h"

static void	set_player_right_images(t_img *img)
{
	img->right_images[0] = "png/dwalk1.png";
	img->right_images[1] = "png/dwalk2.png";
	img->right_images[2] = "png/dwalk3.png";
	img->right_images[3] = "png/dwalk4.png";
	img->right_images[4] = "png/dwalk5.png";
	img->right_images[5] = "png/dwalk6.png";
	img->right_images[6] = "png/dwalk7.png";
	img->right_images[7] = "png/dwalk8.png";
}

static void	set_player_left_images(t_img *img)
{
	img->left_images[0] = "png/dwalk1_left.png";
	img->left_images[1] = "png/dwalk2_left.png";
	img->left_images[2] = "png/dwalk3_left.png";
	img->left_images[3] = "png/dwalk4_left.png";
	img->left_images[4] = "png/dwalk5_left.png";
	img->left_images[5] = "png/dwalk6_left.png";
	img->left_images[6] = "png/dwalk7_left.png";
	img->left_images[7] = "png/dwalk8_left.png";
}

int	init_player_images(t_game *game, t_list **llist)
{
	t_img	*img;

	if (!load_image_to_struct(llist, "png/DwarfSprite1.png", game->mlx))
		return (0);
	img = (t_img *)(*llist)->content;
	set_player_right_images(img);
	set_player_left_images(img);
	img->r_idle_images[0] = "png/DwarfSprite1.png";
	img->l_idle_images[0] = "png/DwarfSprite_left.png";
	init_image_indexes(img, 7, 7);
	return (1);
}

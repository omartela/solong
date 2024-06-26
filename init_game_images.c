/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_images.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartela <omartela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 23:03:40 by omartela          #+#    #+#             */
/*   Updated: 2024/06/27 14:58:10 by omartela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

void	resize_images(t_list **llist)
{
	resize_image((*llist)->content, TILE_SIZE, TILE_SIZE);
	resize_image((*llist)->next->content, TILE_SIZE, TILE_SIZE);
	resize_image((*llist)->next->next->content, TILE_SIZE, TILE_SIZE);
	resize_image((*llist)->next->next->next->content, TILE_SIZE, TILE_SIZE);
}

void	init_game_images(t_game *game, t_list **llist)
{
	load_image_to_struct(llist, "png/DwarfSprite1.png", game->mlx);
	load_image_to_struct(llist, "png/amethyst.png", game->mlx);
	load_image_to_struct(llist, "png/Rock Pile 1.PNG", game->mlx);
	load_image_to_struct(llist, "png/Door02.png", game->mlx);
	resize_images(llist);
}

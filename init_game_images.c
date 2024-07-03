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
	resize_image((*llist)->content, T_SIZE, T_SIZE);
	resize_image((*llist)->next->content, T_SIZE, T_SIZE);
	resize_image((*llist)->next->next->content, T_SIZE, T_SIZE);
	resize_image((*llist)->next->next->next->content, T_SIZE, T_SIZE);
}

int	init_game_images(t_game *game, t_list **llist)
{
	if (!load_image_to_struct(llist, "png/DwarfSprite1.png", game->mlx))
	{
		exit_game(game, 1);
		return (0);
	}
	if (!load_image_to_struct(llist, "png/amethyst.png", game->mlx))
	{
		exit_game(game, 1);
		return (0);
	}
	if (!load_image_to_struct(llist, "png/Rock Pile 1.PNG", game->mlx))
	{
		exit_game(game, 1);
		return (0);
	}
	if (!load_image_to_struct(llist, "png/Door02.png", game->mlx))
	{
		exit_game(game, 1);
		return (0);
	}
	resize_images(llist);
	return (1);
}

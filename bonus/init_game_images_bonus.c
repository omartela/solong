/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_images_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartela <omartela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 08:55:03 by omartela          #+#    #+#             */
/*   Updated: 2024/07/18 08:55:09 by omartela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long_bonus.h"

void	init_image_indexes(t_img *img, int last_li_index, int last_ri_index)
{
	img->ri = 0;
	img->i_ri = 0;
	img->i_li = 0;
	img->li = 0;
	img->last_ri_index = last_ri_index;
	img->last_li_index = last_li_index;
	img->previous_dir = 'r';
}

static void	resize_images(t_list **llist)
{
	void	*content;

	content = (*llist)->next->next->next->next->content;
	resize_image((*llist)->content, T_SIZE, T_SIZE);
	resize_image((*llist)->next->content, T_SIZE, T_SIZE);
	resize_image((*llist)->next->next->content, T_SIZE, T_SIZE);
	resize_image((*llist)->next->next->next->content, T_SIZE, T_SIZE);
	resize_image(content, T_SIZE, T_SIZE);
}

int	init_game_images(t_game *game, t_list **llist)
{
	mlx_put_string(game->mlx, "Move count:", 0, 0);
	mlx_put_string(game->mlx, "Score:", 17 * 10, 0);
	game->move_count_image = mlx_put_string(game->mlx, "0", 12 * 10, 0);
	game->score_image = mlx_put_string(game->mlx, "0", 24 * 10, 0);
	if (!init_player_images(game, llist))
		return (0);
	if (!load_image_to_struct(llist, "png/amethyst.png", game->mlx))
		return (0);
	if (!load_image_to_struct(llist, "png/Rock Pile 1.PNG", game->mlx))
		return (0);
	if (!load_image_to_struct(llist, "png/Door02.png", game->mlx))
		return (0);
	if (!init_enemy_images(game, llist))
		return (0);
	resize_images(llist);
	return (1);
}

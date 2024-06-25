/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartela <omartela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 23:03:40 by omartela          #+#    #+#             */
/*   Updated: 2024/06/25 23:18:42 by omartela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	init_image_indexes(t_img *img)
{
	img->ri = 0;
	img->i_ri = 0;
	img->i_li = 0;
	img->li = 0;
}

void	init_enemy_images(t_game *game, t_list **llist)
{
	t_img	*img;

	load_image_to_struct(llist, "png/goblinright-1.png", game->mlx);
	img = (t_img *)(*llist)->next->next->next->next->content;
	img->last_ri_index = 8;
	img->last_li_index = 8;
	img->right_images[0] = "png/goblinright-1.png";
	img->right_images[1] = "png/goblinright-2.png";
	img->right_images[2] = "png/goblinright-3.png";
	img->right_images[3] = "png/goblinright-4.png";
	img->right_images[4] = "png/goblinright-5.png";
	img->right_images[5] = "png/goblinright-6.png";
	img->right_images[6] = "png/goblinright-7.png";
	img->right_images[7] = "png/goblinright-8.png";
	img->right_images[8] = "png/goblinright-9.png";
	img->left_images[0] = "png/goblinleft-1.png";
	img->left_images[1] = "png/goblinleft-2.png";
	img->left_images[2] = "png/goblinleft-3.png";
	img->left_images[3] = "png/goblinleft-4.png";
	img->left_images[4] = "png/goblinleft-5.png";
	img->left_images[5] = "png/goblinleft-6.png";
	img->left_images[6] = "png/goblinleft-7.png";
	img->left_images[7] = "png/goblinleft-8.png";
	img->left_images[8] = "png/goblinleft-9.png";
	img->r_idle_images[0] = "png/goblinright-1.png";
	img->l_idle_images[0] = "png/goblinleft-1.png";
	img->previous_dir = 'r';
	init_image_indexes(img);
}

void	init_player_images(t_game *game, t_list **llist)
{
	t_img *img;

	load_image_to_struct(llist, "png/DwarfSprite1.png", game->mlx);
	img = (t_img *)(*llist)->content;
	img->last_ri_index = 7;
	img->last_li_index = 7;
	img->right_images[0] = "png/dwalk1.png";
	img->right_images[1] = "png/dwalk2.png";
	img->right_images[2] = "png/dwalk3.png";
	img->right_images[3] = "png/dwalk4.png";
	img->right_images[4] = "png/dwalk5.png";
	img->right_images[5] = "png/dwalk6.png";
	img->right_images[6] = "png/dwalk7.png";
	img->right_images[7] = "png/dwalk8.png";
	img->left_images[0] = "png/dwalk1_left.png";
	img->left_images[1] = "png/dwalk2_left.png";
	img->left_images[2] = "png/dwalk3_left.png";
	img->left_images[3] = "png/dwalk4_left.png";
	img->left_images[4] = "png/dwalk5_left.png";
	img->left_images[5] = "png/dwalk6_left.png";
	img->left_images[6] = "png/dwalk7_left.png";
	img->left_images[7] = "png/dwalk8_left.png";
	img->r_idle_images[0] = "png/DwarfSprite1.png";
	img->l_idle_images[0] = "png/DwarfSprite_left.png";
	img->previous_dir = 'r';
	init_image_indexes(img);
}

void	resize_images(t_list **llist)
{
	resize_image((*llist)->content, TILE_SIZE, TILE_SIZE);
	resize_image((*llist)->next->content, TILE_SIZE, TILE_SIZE);
	resize_image((*llist)->next->next->content, TILE_SIZE, TILE_SIZE);
	resize_image((*llist)->next->next->next->content, TILE_SIZE, TILE_SIZE);
	resize_image((*llist)->next->next->next->next->content, TILE_SIZE, TILE_SIZE);
}

void	init_game_images(t_game *game, t_list **llist)
{
	t_img	*img;

	mlx_put_string(game->mlx, "Move count:", 0, 0);
	mlx_put_string(game->mlx, "Score:", 17 * 10, 0);
	game->move_count_image = mlx_put_string(game->mlx, "0", 12 * 10, 0);
	game->score_image = mlx_put_string(game->mlx, "0", 24 * 10, 0);
	load_image_to_struct(llist, "png/amethyst.png", game->mlx);
	load_image_to_struct(llist, "png/Rock Pile 1 - AZURE - small.PNG", game->mlx);
	load_image_to_struct(llist, "png/Door02.png", game->mlx);
	init_player_images(game, llist);
	init_enemy_images(game, llist);
	resize_images(llist);
}

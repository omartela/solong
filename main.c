/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartela <omartela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 10:05:25 by omartela          #+#    #+#             */
/*   Updated: 2024/06/17 11:38:16 by omartela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

void	init_game_images(t_game *game, t_list **llist)
{
	t_img	*img;

	load_image_to_struct(llist, "DwarfSprite1.png", game->mlx);
	img = (t_img *)(*llist)->content;
	img->right_images[0] = "dwalk1.png";
	img->right_images[1] = "dwalk2.png";
	img->right_images[2] = "dwalk3.png";
	img->right_images[3] = "dwalk4.png";
	img->right_images[4] = "dwalk5.png";
	img->right_images[5] = "dwalk6.png";
	img->right_images[6] = "dwalk7.png";
	img->right_images[7] = "dwalk8.png";
	img->left_images[0] = "dwalk1_left.png";
	img->left_images[1] = "dwalk2_left.png";
	img->left_images[2] = "dwalk3_left.png";
	img->left_images[3] = "dwalk4_left.png";
	img->left_images[4] = "dwalk5_left.png";
	img->left_images[5] = "dwalk6_left.png";
	img->left_images[6] = "dwalk7_left.png";
	img->left_images[7] = "dwalk8_left.png";
	img->r_idle_images[0] = "DwarfSprite1.png";
	img->l_idle_images[0] = "DwarfSprite_left.png";
	img->previous_dir = 'r';
	img->ri = 0;
	img->i_ri = 0;
	img->i_li = 0;
	img->li = 0;
	load_image_to_struct(llist, "amethyst.png", game->mlx);
	load_image_to_struct(llist, "Rock Pile 1 - AZURE - small.PNG", game->mlx);
	load_image_to_struct(llist, "Door02.png", game->mlx);
	resize_image((*llist)->content, TILE_SIZE, TILE_SIZE);
	resize_image((*llist)->next->content, TILE_SIZE, TILE_SIZE);
	resize_image((*llist)->next->next->content, TILE_SIZE, TILE_SIZE);
	resize_image((*llist)->next->next->next->content, TILE_SIZE, TILE_SIZE);
}

void	init_game_variables(t_game *game)
{
	game->players = 0;
	game->exits = 0;
	game->collectibles = 0;
	game->move_count = 0;
}

int	init_game(t_game *game)
{
	mlx_t		*mlx;
	t_list		*llist;

	llist = NULL;
	init_game_variables(game);
	read_map(game);
	if (!validate_map(game))
	{
		free_map(game->map, game->map_height);
		return (0);
	}
	mlx = mlx_init(480, 480, "Dwarf & Diamonds", true);
	if (!mlx)
		error();
	game->mlx = mlx;
	init_game_images(game, &llist);
	extract_map_data(game, &llist);
	game->llist = llist;
	mlx_key_hook(mlx, &ft_hook_movement, game);
	mlx_loop(mlx);
    // Optional, terminate will clean up any leftover images (not textures!)
	ft_lstclear(&llist, &delete_img_node);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}

int	main(int argc, char *argv[])
{
	t_game		game;

	if (argc == 2)
	{
		game.filename = argv[1];
		init_game(&game);
	}
}

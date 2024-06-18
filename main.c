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
	img->right_images[0] = "right1.png";
	img->right_images[1] = "right2.png";
	img->right_images[2] = "right3.png";
	img->idle_images[0] = "DwarfSprite1.png";
	img->ri = 0;
	img->ii = 0;
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

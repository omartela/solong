/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartela <omartela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 14:25:10 by omartela          #+#    #+#             */
/*   Updated: 2024/06/27 12:21:52 by omartela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

unsigned int	seed = 100;

unsigned int	lcg()
{
	seed = (LCG_A * seed + LCG_C) % LCG_M;
	return (seed);
}

int	generate_random_number(int min, int max)
{
	return (min + (lcg() % (max - min + 1)));
}

char	get_direction_from_num(int number)
{
	if (number == 1)
		return ('u');
	if (number == 2)
		return ('d');
	if (number == 3)
		return ('l');
	if (number == 4)
		return ('r');
	return ('r');
}

void	animation(char direction, void *content)
{
	mlx_image_t	*mlx_image;
	t_img		*img;

	img = (t_img *)content;
	mlx_image = img->image;
	if (direction == 'r')
	{
		if (img->previous_dir != direction)
		{
			load_image(img->r_idle_images[0], img->mlx, img);
			img->ri = 0;
		}
		else if (img->ri == img->last_ri_index)
		{
			load_image(img->r_idle_images[0], img->mlx, img);
			img->ri = 0;
		}
		else
		{
			load_image(img->right_images[img->ri], img->mlx, img);
			img->ri += 1;
		}
		img->previous_dir = 'r';
	}
	if (direction == 'l')
	{
		if (img->previous_dir != direction)
		{
			load_image(img->l_idle_images[0], img->mlx, img);
			img->li = 0;
		}
		else if (img->li == img->last_li_index)
		{
			load_image(img->l_idle_images[0], img->mlx, img);
			img->li = 0;
		}
		else
		{
			load_image(img->left_images[img->li], img->mlx, img);
			img->li += 1;
		}
		img->previous_dir = 'l';
	}
	resize_image(content, TILE_SIZE, TILE_SIZE);
	insert_image_to_window(content, mlx_image->instances[0].x, mlx_image->instances[0].y);
	mlx_delete_image(img->mlx, mlx_image);
}

void	move_enemy(void *content)
{
	int	number;
	t_img	*enemy;
	t_game 	*game;
	char	direction;

	game = (t_game *)content;
	enemy = game->llist->next->next->next->next->content;

	number = generate_random_number(1, 4);
	direction = get_direction_from_num(number);
	seed += 1; 
	while (direction == enemy->previous_dir)
		direction = get_direction_from_num(generate_random_number(1,4));
	if (direction == 'u')
	{
		if (!check_obstacle(game->llist->next->next->content, enemy, -TILE_SIZE, 'y' ))
		{
			enemy->image->instances[0].y -= TILE_SIZE;
			enemy->previous_dir = 'u';
		}
	}
	else if (direction == 'd')
	{
		if (!check_obstacle(game->llist->next->next->content, enemy, TILE_SIZE, 'y' ))
		{
			enemy->image->instances[0].y += TILE_SIZE;
			enemy->previous_dir = 'd';
		}
	}
	else if (direction == 'l')
	{
		if (!check_obstacle(game->llist->next->next->content, enemy, -TILE_SIZE, 'x' ))
		{
			enemy->image->instances[0].x -= TILE_SIZE; 
			animation('l', game->llist->next->next->next->next->content);
			enemy->previous_dir = 'l';
		}
	}
	else if (direction == 'r')
	{
		if (!check_obstacle(game->llist->next->next->content, enemy, TILE_SIZE, 'x' ))
		{
			enemy->image->instances[0].x += TILE_SIZE;
			animation('r', game->llist->next->next->next->next->content);
			enemy->previous_dir = 'r';
		}
	}
}

void	move_up(t_game *game)
{
	t_list	*llist;
	t_img	*player;

	llist = game->llist;
	player = llist->content;
	if (!check_obstacle(llist->next->next->content, player, -TILE_SIZE, 'y'))
	{
		player->image->instances[0].y -= TILE_SIZE;
		if (check_collectable(llist->next->content, player))
			game->score +=1;
		game->move_count += 1;
	}
}

void	print_moves_and_score(t_game *game)
{
	if (game->move_count_image)
		mlx_delete_image(game->mlx, game->move_count_image);
	game->move_count_image = mlx_put_string(game->mlx, ft_itoa(game->move_count), 12 * 10, 0);
	if (game->score_image)
		mlx_delete_image(game->mlx, game->score_image);
	game->score_image = mlx_put_string(game->mlx, ft_itoa(game->score), 25 * 10, 0);
}

void	move_down(t_game *game)
{
	t_list	*llist;
	t_img	*player;

	llist = game->llist;
	player = llist->content;
	if (!check_obstacle(llist->next->next->content, player, TILE_SIZE, 'y'))
	{
		player->image->instances[0].y += TILE_SIZE;
		if (check_collectable(llist->next->content, player))
			game->score +=1;
		game->move_count += 1;
	}
}

void	move_left(t_game *game)
{
	t_list	*llist;
	t_img	*player;

	llist = game->llist;
	player = llist->content;
	if (!check_obstacle(llist->next->next->content, player, -TILE_SIZE, 'x'))
	{
		player->image->instances[0].x -= TILE_SIZE;
		if (check_collectable(llist->next->content, player))
			game->score += 1;
		game->move_count += 1;
		animation('l', game->llist->content);
	}
}

void	move_right(t_game *game)
{
	t_list	*llist;
	t_img	*player;

	llist = game->llist;
	player = llist->content;
	if (!check_obstacle(llist->next->next->content, player, TILE_SIZE, 'x'))
	{
		player->image->instances[0].x += TILE_SIZE;
		if (check_collectable(llist->next->content, player))
			game->score += 1;	
		game->move_count += 1;	
		animation('r', game->llist->content);
	}
}

void	ft_hook_movement(mlx_key_data_t keydata, void *param)
{
	mlx_t	*mlx;
	t_img	*params;
	t_game	*game;
	t_list	*llist;

	game = (t_game *)param;
	llist = game->llist;
	params = (t_img *)llist->content;
	mlx = params->mlx;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(mlx);
	if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
		move_up(game);
	if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS)
		move_down(game);
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		move_left(game);
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		move_right(game);
	print_moves_and_score(game);
	if (keydata.action == MLX_PRESS)
		move_enemy(game);
	if (check_collision_to_player(llist->next->next->next->next->content, params))
	{
		params->image->instances[0].enabled = false;
	}
	check_exit(game, params);
}

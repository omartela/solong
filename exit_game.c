/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartela <omartela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 23:33:59 by omartela          #+#    #+#             */
/*   Updated: 2024/06/27 14:05:24 by omartela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

void	free_map(char **map, size_t i)
{
	while (i > 0)
	{
		i--;
		free(map[i]);
	}
	free(map);
}

void	free_game_assets(t_game *game)
{
	t_list *llist;

	llist = game->llist;
	free_map(game->map, game->map_height);
	ft_lstclear(&llist, &delete_img_node);
	//mlx_terminate(game->mlx);
}

int	exit_game(t_game *game)
{
	free_game_assets(game);
	mlx_close_window(game->mlx);
	return (EXIT_SUCCESS);
}

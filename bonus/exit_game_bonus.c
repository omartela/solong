/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_game_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartela <omartela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 08:53:57 by omartela          #+#    #+#             */
/*   Updated: 2024/07/18 08:54:00 by omartela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long_bonus.h"

void	error(char *s1)
{
	ft_putstr_fd("Error\n", 1);
	ft_putstr_fd(s1, 1);
	puts(mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

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
	t_list	*llist;

	llist = game->llist;
	free_map(game->map, game->map_height);
	ft_lstclear(&llist, &delete_img_node);
}

int	exit_game(t_game *game, int flag)
{
	if (flag)
	{
		mlx_close_window(game->mlx);
		free_game_assets(game);
		return (1);
	}
	return (0);
}

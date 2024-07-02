/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartela <omartela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 14:02:33 by omartela          #+#    #+#             */
/*   Updated: 2024/07/02 09:14:38 by omartela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

void	push(t_bfs *bfs, int x, int y)
{
	bfs->q[bfs->back][0] = x;
	bfs->q[bfs->back][1] = y;
	bfs->back++;
}

void	pop(t_bfs *bfs)
{
	bfs->q[bfs->front][0] = 0;
	bfs->q[bfs->front][1] = 0;
	bfs->front++;
}

void	check_directions(t_bfs *bfs, t_game *game, int current_x, int current_y)
{
	size_t	new_x;
	size_t	new_y;
	int		i;

	i = 0;
	while (i < 4)
	{
		new_x = current_x + bfs->directions[i][0];
		new_y = current_y + bfs->directions[i][1];
		if (new_x < game->map_width && new_y < game->map_height
			&& game->map[new_y][new_x] != '1'
			&& bfs->visited[new_y][new_x] == 0)
		{
			bfs->visited[new_y][new_x] = 1;
			push(bfs, new_x, new_y);
		}
		++i;
	}
}

void	bfs(t_game *game, t_bfs	*bfs)
{
	int		current_x;
	int		current_y;

	push(bfs, game->player_x, game->player_y);
	bfs->visited[game->player_x][game->player_y] = 1;
	while (bfs->front != bfs->back)
	{
		current_x = bfs->q[bfs->front][0];
		current_y = bfs->q[bfs->front][1];
		pop(bfs);
		check_directions(bfs, game, current_x, current_y);
	}
}

int	start_bfs(t_game *game)
{
	t_bfs	bfs_s;

	init_bfs(&bfs_s);
	find_player_pos(game);
	bfs(game, &bfs_s);
	return (check_visited(game, &bfs_s));
}

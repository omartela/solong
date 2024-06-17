/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartela <omartela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 14:02:33 by omartela          #+#    #+#             */
/*   Updated: 2024/06/17 11:44:39 by omartela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include "so_long.h"

void	init_bfs(t_bfs *bfs)
{
	int	i;

	i = 0;
	bfs->front = 0;
	bfs->back = 0;
	bfs->directions[0][0] = 0;
	bfs->directions[0][1] = 1;
	bfs->directions[1][0] = 1;
	bfs->directions[1][1] = 0;
	bfs->directions[2][0] = 0;
	bfs->directions[2][1] = -1;
	bfs->directions[3][0] = -1;
	bfs->directions[3][1] = 0;
	while (i < 100)
	{
		ft_bzero(bfs->visited[i], 100);
		++i;
	}
}

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
		if (new_x >= 0 && new_x < game->map_width && new_y >= 0 && new_y < game->map_height && game->map[new_x][new_y] != '1' && bfs->visited[new_x][new_y] == 0)
		{
			bfs->visited[new_x][new_y] = 1;
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

int	check_col_exits_player(t_game *game, t_bfs *bfs)
{
	size_t	i;
	size_t	j;
	int		collectibles_visited;
	int		exit_visited;

	i = 0;
	j = 0;
	collectibles_visited = 1;
	exit_visited = 1;
	while (i < game->map_height)
	{
		j = 0;
		while (j < game->map_height)
		{
			if (game->map[j][i] == 'C' && bfs->visited[j][i] == 0)
				collectibles_visited = 0;
			if (game->map[i][j] == 'E' && bfs->visited[i][j] == 0)
				exit_visited = 0;
			++j;
		}
		++i;
	}
	if (collectibles_visited && exit_visited)
	{
		printf("map is valid\n");
		return (1);
	}
	printf("map invalid\n");
	return (0);
}

void	find_player_pos(t_game *game)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (j < game->map_height)
	{
		i = 0;
		while (i < game->map_width)
		{
			if (game->map[j][i] == 'P')
			{
				game->player_x = i;
				game->player_y = j;
			}
			++i;
		}
		++j;
	}
}

int	start_bfs(t_game *game) 
{
	size_t	i;
	size_t	j;
	t_bfs	bfs_s;

	i = 0;
	j = 0;
	init_bfs(&bfs_s);
	find_player_pos(game);
	bfs(game, &bfs_s);
	return (check_col_exits_player(game, &bfs_s));
}


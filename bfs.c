/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartela <omartela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 14:02:33 by omartela          #+#    #+#             */
/*   Updated: 2024/06/13 20:25:25 by omartela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include "so_long.h"

int	visited[15][15] = {0};

void	init_bfs(t_bfs *bfs)
{
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

void	check_directions(t_bfs *bfs, char **game_map, int current_x, int current_y)
{
	int	new_x;
	int	new_y;
	int	i;

	i = 0;
	while (i < 4)
	{
		new_x = current_x + bfs->directions[i][0];
		new_y = current_y + bfs->directions[i][1];
		if (new_x >= 0 && new_x < 15 && new_y >= 0 && new_y < 15 && game_map[new_x][new_y] != '1' && visited[new_x][new_y] == 0)
		{
			visited[new_x][new_y] = 1;
			push(bfs, new_x, new_y);
		}
		++i;
	}
}

void	bfs(char **game_map, int start_x, int start_y)
{
	t_bfs	bfs;
	int		current_x;
	int		current_y;

	init_bfs(&bfs);
	push(&bfs, start_x, start_y);
	visited[start_x][start_y] = 1;
	while (bfs.front != bfs.back)
	{
		current_x = bfs.q[bfs.front][0];
		current_y = bfs.q[bfs.front][1];
		pop(&bfs);
		check_directions(&bfs, game_map, current_x, current_y);
	}
}

int	start_bfs(t_game *game) 
{
	size_t	i;
	size_t	j;
	int		collectibles_visited = 1;
	int 	exit_visited = 1;


	i = 0;
	j = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (j < game->map_height)
		{
			if (game->map[j][i] == 'P')
			{
				break;
			}
			++j;
		}
		++i;
	}
	bfs(game->map, i, j);
	i = 0;
	j = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (j < game->map_height)
		{
			if (game->map[j][i] == 'C' && visited[j][i] == 0)
			{
				collectibles_visited = 0;
			}
			if (game->map[i][j] == 'E' && visited[i][j] == 0)
			{
				exit_visited = 0;
			}
			++j;
		}
		++i;
	}
	printf("collectibles visited %d\n", collectibles_visited);
	if (collectibles_visited && exit_visited)
	{
		printf("map is valid\n");
		return (1);
	}
	printf("map invalid\n");
	return (0);
}


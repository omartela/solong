/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartela <omartela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 14:02:33 by omartela          #+#    #+#             */
/*   Updated: 2024/06/12 11:35:40 by omartela         ###   ########.fr       */
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
	printf("test in bfs function \n");
	printf("testing %d, %d", start_x, start_y);
	push(&bfs, start_x, start_y);
	visited[start_x][start_y] = 1;
	while (bfs.front != bfs.back)
	{
		current_x = bfs.q[bfs.front][0];
		current_y = bfs.q[bfs.front][1];
		printf("(%d, %d) -> ", current_x, current_y);
		pop(&bfs);
		check_directions(&bfs, game_map, current_x, current_y);
	}
}

int	start_bfs(char **game_map, size_t y) 
{
	size_t	start_x;
	size_t	start_y;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < y)
	{
		j = 0;
		while (j < y)
		{
			if (game_map[i][j] == 'P')
			{
				start_x = i;
				start_y = j;
				break;
			}
			++j;
		}
		++i;
	}
	bfs(game_map, start_x, start_y);

	int collectibles_visited = 1;
	int exit_visited = 1;

	i = 0;
	j = 0;

	while (i < y)
	{
		while (j < y)
		{
			if (game_map[i][j] == 'C' && visited[i][j] == 0)
			{
				collectibles_visited = 0;
			}
			if (game_map[i][j] == 'E' && visited[i][j] == 0)
			{
				exit_visited = 0;
			}
			++j;
		}
		++i;
	}

	printf("collectibles_visited %d\n", collectibles_visited);
	printf("exit_visited %d\n", exit_visited);
	if (collectibles_visited && exit_visited)
		printf("map is valid");

	return (0);
}


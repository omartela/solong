/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartela <omartela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 16:38:47 by omartela          #+#    #+#             */
/*   Updated: 2024/06/27 16:44:09 by omartela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

int	check_visited(t_game *game, t_bfs *bfs)
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
		return (1);
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

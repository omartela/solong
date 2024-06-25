/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartela <omartela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 23:33:59 by omartela          #+#    #+#             */
/*   Updated: 2024/06/25 23:41:21 by omartela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
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
	free_map(game->map, game->map_height);
	ft_lstclear(game->llist, &delete_img_node);
	mlx_terminate(game->mlx);
}

void	exit_game(t_game *game)
{
	free_game_assets(game);
	return (EXIT_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_moves_score_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartela <omartela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 14:18:56 by omartela          #+#    #+#             */
/*   Updated: 2024/07/22 14:18:58 by omartela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long_bonus.h"

void	print_moves_and_score(t_game *game)
{
	mlx_image_t	*img;
	char		*str;

	if (game->move_count_image)
		mlx_delete_image(game->mlx, game->move_count_image);
	str = ft_itoa(game->move_count);
	img = mlx_put_string(game->mlx, str, 12 * 10, 0);
	free(str);
	game->move_count_image = img;
	if (game->score_image)
		mlx_delete_image(game->mlx, game->score_image);
	str = ft_itoa(game->score);
	img = mlx_put_string(game->mlx, str, 25 * 10, 0);
	free(str);
	game->score_image = img;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_enemy2_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartela <omartela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 09:05:39 by omartela          #+#    #+#             */
/*   Updated: 2024/07/23 13:16:42 by omartela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long_bonus.h"
#include "stdio.h"
char get_direction(t_game *game)
{
    t_img *player;
    t_img *enemy;
    t_img *obs;

    obs = (t_img *)game->llist->next->next->content;
    player = (t_img *)game->llist->content;
    enemy = (t_img *)game->llist->next->next->next->next->content;

    // Get positions
    int player_x = player->image->instances[0].x;
    int player_y = player->image->instances[0].y;
    int enemy_x = enemy->image->instances[0].x;
    int enemy_y = enemy->image->instances[0].y;

    // Calculate distances
    int dx = player_x - enemy_x;
    int dy = player_y - enemy_y;
	printf("player x %d, player y %d \n", player_x, player_x);
	printf("enemy x %d, enemy y %d \n", enemy_x, enemy_x);
	printf("%d %d \n", dx, dy);
    // Handle alignment cases
    if (player_x == enemy_x) // Same vertical level
    {
        if (dy < 0 && !check_obstacle(obs, enemy, -T_SIZE, 'y'))
            return 'u';  // Move Up
        if (dy > 0 && !check_obstacle(obs, enemy, T_SIZE, 'y'))
            return 'd';  // Move Down
		if (!check_obstacle(obs, enemy, -T_SIZE, 'x'))
			return ('l');
		if (!check_obstacle(obs, enemy, T_SIZE, 'x'))
			return ('r');
    }
    else if (player_y == enemy_y) // Same horizontal level
    {
        if (dx < 0 && !check_obstacle(obs, enemy, -T_SIZE, 'x'))
            return 'l';  // Move Left
        if (dx > 0 && !check_obstacle(obs, enemy, T_SIZE, 'x'))
            return 'r';  // Move Right
		if (!check_obstacle(obs, enemy, -T_SIZE, 'y'))
			return ('u');
		if (!check_obstacle(obs, enemy, T_SIZE, 'y'))
			return ('d');
    }
    else // Diagonal case
    {
        // Prioritize movement to reduce the largest distance
        if (abs(dx) > abs(dy)) // Larger horizontal distance
        {
            if (dx < 0 && !check_obstacle(obs, enemy, -T_SIZE, 'x'))
                return 'l';  // Move Left
            if (dx > 0 && !check_obstacle(obs, enemy, T_SIZE, 'x'))
                return 'r';  // Move Right
			if (!check_obstacle(obs, enemy, -T_SIZE, 'y'))
				return ('u');
			if (!check_obstacle(obs, enemy, T_SIZE, 'y'))
				return ('d');
        }
        else // Larger vertical distance
        {
            if (dy < 0 && !check_obstacle(obs, enemy, -T_SIZE, 'y'))
                return 'u';  // Move Up
            if (dy > 0 && !check_obstacle(obs, enemy, T_SIZE, 'y'))
                return 'd';  // Move Down
			if (!check_obstacle(obs, enemy, -T_SIZE, 'x'))
				return ('l');
			if (!check_obstacle(obs, enemy, T_SIZE, 'x'))
				return ('r');
        }
    }

    // Default return if no direction is valid
    return 'r';  // Stay
}


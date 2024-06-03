/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartela <omartela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 14:52:19 by omartela          #+#    #+#             */
/*   Updated: 2024/06/03 10:10:33 by omartela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include "MLX42/include/MLX42/MLX42.h"
# include "libft/libft.h"
# include "libft/get_next_line.h"

typedef struct s_img
{
	mlx_t			*mlx;
	mlx_image_t		*image;
	mlx_texture_t	*texture;
}	t_img;

void	load_texture(char *str, t_img *i_s);
void	load_image(char *str, mlx_t *mlx, t_img *i_s);
void	error(void);
void	load_images_to_struct(t_list **llist, char *str, mlx_t *mlx);

#endif

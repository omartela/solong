/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartela <omartela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:32:17 by omartela          #+#    #+#             */
/*   Updated: 2024/06/07 16:17:39 by omartela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

void	load_images_to_struct(t_list **llist, char *str, mlx_t *mlx)
{
	t_img	*img_s;
	t_list	*new;

	img_s = malloc(sizeof(t_img));
	img_s->mlx = mlx;
	load_image(str, mlx, img_s);
	new = ft_lstnew(img_s);
	ft_lstadd_back(llist, new);
}

void	delete_img_node(void *content)
{
	t_img	*img_s;

	img_s = (t_img *)content;
	mlx_delete_image(img_s->mlx, img_s->image);
	free(img_s);
}

void	error(void)
{
	puts(mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

void	load_texture(char *str, t_img *i_s)
{
	mlx_texture_t	*texture;

	texture = mlx_load_png(str);
	if (!texture)
		error();
	i_s->texture = texture;
}

void	load_image(char *str, mlx_t *mlx, t_img *i_s)
{
	mlx_image_t		*img;

	load_texture(str, i_s);
	img = mlx_texture_to_image(mlx, i_s->texture);
	if (!img)
		error();
	i_s->image = img;
	mlx_delete_texture(i_s->texture);
}

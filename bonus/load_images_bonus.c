/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartela <omartela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:32:17 by omartela          #+#    #+#             */
/*   Updated: 2024/06/28 15:45:28 by omartela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long_bonus.h"

void	load_image_to_struct(t_list **llist, char *str, mlx_t *mlx)
{
	t_img	*img_s;
	t_list	*new;

	img_s = malloc(sizeof(t_img));
	if (!img_s)
	{
		ft_lstclear(llist, &delete_img_node);
	}
	else
	{
		img_s->mlx = mlx;
		img_s->texture = NULL;
		load_image(str, mlx, img_s);
		if (img_s->image)
		{
			new = ft_lstnew(img_s);
			ft_lstadd_back(llist, new);
		}
		else
		{
			ft_lstclear(llist, &delete_img_node);
		}
	}
}

void	delete_img_node(void *content)
{
	t_img	*img_s;

	img_s = (t_img *)content;
	if (img_s)
	{
		mlx_delete_image(img_s->mlx, img_s->image);
		free(img_s);
	}
}

void	load_texture(char *str, t_img *i_s)
{
	mlx_texture_t	*texture;

	texture = mlx_load_png(str);
	if (!texture)
		error("Load texture failed");
	i_s->texture = texture;
}

void	load_image(char *str, mlx_t *mlx, t_img *i_s)
{
	mlx_image_t		*img;

	load_texture(str, i_s);
	if (i_s->texture)
	{
		img = mlx_texture_to_image(mlx, i_s->texture);
		mlx_delete_texture(i_s->texture);
	}
	if (!img)
		error("Load image failed");
	i_s->image = img;
}

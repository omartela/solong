/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_images_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartela <omartela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 08:55:28 by omartela          #+#    #+#             */
/*   Updated: 2024/07/26 10:32:26 by omartela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long_bonus.h"

int	load_image_to_struct(t_list **llist, char *str, mlx_t *mlx)
{
	t_img	*img_s;
	t_list	*new;

	img_s = malloc(sizeof(t_img));
	if (!img_s)
		return (0);
	else
	{
		img_s->mlx = mlx;
		img_s->texture = NULL;
		if (load_image(str, mlx, img_s))
		{
			new = ft_lstnew(img_s);
			ft_lstadd_back(llist, new);
			return (1);
		}
		else
		{
			free(img_s);
			return (0);
		}
	}
	return (1);
}

void	delete_img_node(void *content)
{
	t_img	*img_s;

	img_s = (t_img *)content;
	if (img_s)
	{
		if (img_s->image)
			mlx_delete_image(img_s->mlx, img_s->image);
		free(img_s);
	}
}

int	load_texture(char *str, t_img *i_s)
{
	mlx_texture_t	*texture;

	texture = mlx_load_png(str);
	if (!texture)
	{
		error("Load texture failed\n");
		return (0);
	}
	i_s->texture = texture;
	return (1);
}

int	load_image(char *str, mlx_t *mlx, t_img *i_s)
{
	mlx_image_t		*img;

	img = NULL;
	i_s->image = img;
	if (load_texture(str, i_s))
	{
		img = mlx_texture_to_image(mlx, i_s->texture);
		mlx_delete_texture(i_s->texture);
	}
	else
		return (0);
	if (!img)
	{
		error("Load image failed\n");
		return (0);
	}
	i_s->image = img;
	return (1);
}

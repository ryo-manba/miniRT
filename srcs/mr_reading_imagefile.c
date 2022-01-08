/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mr_reading_imagefile.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 22:47:00 by corvvs            #+#    #+#             */
/*   Updated: 2022/01/07 23:45:14 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	destroy_image(t_info *info, t_img *img)
{
	if (!img)
		return ;
	if (img->img)
	{
		mlx_destroy_image(info->mlx, img->img);
	}
	free(img);
}

static bool	read_xmp_image(t_info *info, t_scene *scene, t_element *el)
{
	char	*xpm_path;
	t_img	*image;

	el->image = ft_calloc(1, sizeof(t_img));
	if (!el->image)
	{
		mr_destroy_image_files(info, scene);
		return (false);
	}
	xpm_path = el->xpm_file_path;
	image = el->image;
	image->img = mlx_xpm_file_to_image(info->mlx,
			xpm_path, &image->width, &image->height);
	printf("%p %d %d\n", image->img, image->width, image->height);
	if (!image->img)
	{
		mr_destroy_image_files(info, scene);
		return (false);
	}
	image->addr = mlx_get_data_addr(
			image->img,
			&image->bpp,
			&image->line_len,
			&image->endian);
	return (!!image->addr);
}

void	mr_destroy_image_files(t_info *info, t_scene *scene)
{
	t_element	**objects;
	size_t		i;

	printf("destroying images\n");
	i = 0;
	objects = scene->objects;
	while (i < scene->n_objects)
	{
		if (objects[i]->tex_el)
		{
			printf("destroying texture %zu: %s\n",
				i, objects[i]->tex_el->xpm_file_path);
			destroy_image(info, objects[i]->tex_el->image);
		}
		if (objects[i]->bump_el)
		{
			printf("destroying bumpmap %zu: %s\n",
				i, objects[i]->bump_el->xpm_file_path);
			destroy_image(info, objects[i]->bump_el->image);
		}
		i += 1;
	}
}

bool	mr_read_image_files(t_info *info, t_scene *scene)
{
	t_element	**objects;
	size_t		i;

	i = 0;
	objects = scene->objects;
	while (i < scene->n_objects)
	{
		if (objects[i]->tex_el && objects[i]->tex_el->etype == RD_ET_TEXTURE)
		{
			if (!read_xmp_image(info, scene, objects[i]->tex_el))
			{
				return (false);
			}
		}
		if (objects[i]->bump_el && objects[i]->bump_el->etype == RD_ET_BUMPMAP)
		{
			if (!read_xmp_image(info, scene, objects[i]->bump_el))
			{
				return (false);
			}
		}
		i += 1;
	}
	return (true);
}

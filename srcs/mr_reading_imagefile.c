/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mr_reading_imagefile.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 22:47:00 by corvvs            #+#    #+#             */
/*   Updated: 2022/01/17 00:46:20 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	destroy_image(t_info *info, t_img **pimg)
{
	t_img	*img;

	if (!pimg)
		return ;
	img = *pimg;
	if (!img)
		return ;
	if (img->img)
	{
		mlx_destroy_image(info->mlx, img->img);
		img->img = NULL;
	}
	free(img);
	*pimg = NULL;
}

static void	read_xmp_image(t_info *info, t_element *el, const char *error)
{
	char	*xpm_path;
	t_img	*image;

	el->image = ft_calloc(1, sizeof(t_img));
	if (!el->image)
		mr_bailout(info, error);
	xpm_path = el->xpm_file_path;
	image = el->image;
	image->img = mlx_xpm_file_to_image(info->mlx,
			xpm_path, &image->width, &image->height);
	if (!image->img)
		mr_bailout(info, error);
	image->addr = mlx_get_data_addr(
			image->img,
			&image->bpp,
			&image->line_len,
			&image->endian);
	if (!image->addr)
		mr_bailout(info, error);
}

// destroy all (loaded) images for texture / bumpmap elements.
void	mr_destroy_image_files(t_info *info)
{
	t_element	**objects;
	size_t		i;

	i = 0;
	objects = info->scene->objects;
	while (i < info->scene->n_objects)
	{
		if (objects[i]->tex_el)
			destroy_image(info, &objects[i]->tex_el->image);
		if (objects[i]->bump_el)
			destroy_image(info, &objects[i]->bump_el->image);
		i += 1;
	}
	i = 0;
	objects = info->scene->spotlights;
	while (i < info->scene->n_spotlights)
	{
		if (objects[i]->xpm_file_path)
			destroy_image(info, &objects[i]->image);
		i += 1;
	}
}

// for all texture or bumpmap elements,
// read images from attached xpm_file_path.
bool	mr_read_image_files(t_info *info)
{
	t_element	**objects;
	size_t		i;

	i = 0;
	objects = info->scene->objects;
	while (i < info->scene->n_objects)
	{
		if (objects[i]->tex_el && objects[i]->tex_el->etype == RD_ET_TEXTURE)
			read_xmp_image(info, objects[i]->tex_el, "bad texture");
		if (objects[i]->bump_el && objects[i]->bump_el->etype == RD_ET_BUMPMAP)
			read_xmp_image(info, objects[i]->bump_el, "bad bumpmap");
		i += 1;
	}
	i = 0;
	objects = info->scene->spotlights;
	while (i < info->scene->n_spotlights)
	{
		if (objects[i]->xpm_file_path)
			read_xmp_image(info, objects[i], "bad projection image");
		i += 1;
	}
	return (true);
}

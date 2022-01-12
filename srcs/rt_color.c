/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_color.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 00:01:16 by rmatsuka          #+#    #+#             */
/*   Updated: 2022/01/12 02:56:53 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_vec3	color_at(
	t_img *image,
	int x, int y
)
{
	t_vec3				cv;
	const unsigned int	color = mr_mlx_pixel_get(image, x, y);

	cv.x = ((color >> 16) & 0xff) / 255.0;
	cv.y = ((color >> 8) & 0xff) / 255.0;
	cv.z = (color & 0xff) / 255.0;
	return (cv);
}

t_vec3	rt_color_texture(double u, double v, t_element *el)
{
	t_img		*texture;
	double		jd;
	double		id;

	texture = el->image;
	jd = fmod(u * texture->width * el->freq_u + \
			100000 * texture->width, texture->width);
	id = fmod(v * texture->height * el->freq_v + \
			100000 * texture->height, texture->height);
	return (color_at((t_img *)texture, jd, id));
}

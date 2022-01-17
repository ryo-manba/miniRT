/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_color.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 00:01:16 by rmatsuka          #+#    #+#             */
/*   Updated: 2022/01/17 20:16:28 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	rt_sky_blue(const t_vec3 direction)
{
	const t_vec3	c2 = {1.0, 1.0, 1.0};
	const t_vec3	c1 = {0.5, 0.7, 1.0};
	const t_vec3	unit_direction = mr_unit_vector(&direction);
	const double	t = 0.5 * (unit_direction.y + 1.0);

	return (mr_vec3_add(
			mr_vec3_mul_double(&c1, t),
			mr_vec3_mul_double(&c2, 1 - t)));
}

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

t_vec3	rt_color_image(double u, double v, t_element *el)
{
	t_img		*image;
	double		jd;
	double		id;

	image = el->image;
	if (el->etype == RD_ET_PYRAMIDLIGHT)
	{
		jd = rt_fmod(u * image->width, image->width);
		id = rt_fmod(v * image->height, image->height);
	}
	else
	{
		jd = rt_fmod(u * image->width * el->freq_u, image->width);
		id = rt_fmod(v * image->height * el->freq_v, image->height);
	}
	return (color_at(image, jd, id));
}

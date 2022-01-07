/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_color.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 00:01:16 by rmatsuka          #+#    #+#             */
/*   Updated: 2022/01/07 20:33:37 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define SHIFT_T 24
#define SHIFT_R 16
#define SHIFT_G 8
#define SHIFT_B 0

int	rt_create_trgb(int t, int r, int g, int b)
{
	return (t << SHIFT_T | r << SHIFT_R | g << SHIFT_G | b);
}

t_vec3	rt_color_at(
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

double	rt_grayscale_color_at(
	t_img *image,
	int x,
	int y
)
{
	const unsigned int	color = mr_mlx_pixel_get(image, x, y);

	return ((color & 0xff) / 255.0);
}

t_vec3	rt_element_color(double u, double v, t_element *el)
{
	t_img		*texture;
	double		jd;
	double		id;
	int			ji;
	int			ii;

	texture = el->image;
	jd = fmod(u * texture->width * el->freq_u + \
			100000 * texture->width, texture->width);
	id = fmod(v * texture->height * el->freq_v + \
			100000 * texture->height, texture->height);
	ji = jd;
	ii = id;
	return (rt_color_at((t_img *)texture, ji, ii));
}

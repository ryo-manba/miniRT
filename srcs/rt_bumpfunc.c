/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_bumpfunc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 02:22:27 by corvvs            #+#    #+#             */
/*   Updated: 2021/12/28 16:03:01 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#define IMAGE_W 6
#define IMAGE_H 6
// static const double g_bumpmap[IMAGE_H][IMAGE_W] = {
// 	{0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
// 	{0.0, 0.3, 0.6, 0.6, 0.3, 0.0},
// 	{0.0, 0.6, 0.9, 0.9, 0.6, 0.0},
// 	{0.0, 0.6, 0.9, 0.9, 0.6, 0.0},
// 	{0.0, 0.3, 0.6, 0.6, 0.3, 0.0},
// 	{0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
// };

static double	color_at(
	t_img *bumpmap,
	int x, int y
)
{
	const unsigned int color = mr_mlx_pixel_get(bumpmap, x, y);
	return ((double)(color & 0xff));
}

t_vec3	test_bumpfunc_image(double u, double v, t_img *bumpmap)
{
	double jd = fmod(u * bumpmap->width + 100000 * bumpmap->width, bumpmap->width);
	double id = fmod(v * bumpmap->height + 100000 * bumpmap->height, bumpmap->height);
	int ji = jd;
	int ii = id;
	const double	h1 = color_at(bumpmap, ji, ii);
	const double	h2 = color_at(bumpmap, (ji + 1) % bumpmap->width, ii);
	const double	h3 = color_at(bumpmap, ji, (ii + 1) % bumpmap->height);
	const double	h4 = color_at(bumpmap, (ji + 1) % bumpmap->width, (ii + 1) % bumpmap->height);
	const double	ru = jd - (double)ji;
	const double	rv = id - (double)ii;
	const double	c = 1e-2;
	double			norm;
	t_vec3			n;
	n.x = c * ((h1 - h2 - h3 + h4) * rv + (h2 - h4));
	n.y = c * ((h1 - h2 - h3 + h4) * ru + (h3 - h4));
	// n.z = -1;
	// norm = -1 / sqrt(pow(n.x, 2) + pow(n.y, 2) + pow(n.z, 2));
	norm = -1 / sqrt(pow(n.x, 2) + pow(n.y, 2) + 1);
	n.x *= norm;
	n.y *= norm;
	// n.z *= norm;
	n.z = -norm;
	return (n);
}

t_vec3 test_bumpfunc_wave2(double u, double v)
{
	const double	c = 2e-1;
	double			norm;
	t_vec3			n;

	// g(u, v) = c * sin(u) * sin(v)
	// f(u, v, w) = g(u, v) - w
	// then, grad f is:
	n.x = c * cos(u) * sin(v);
	n.y = c * sin(u) * cos(v);
	// n.z = -1;
	// normalize and invert grad f:
	norm = -1 / sqrt(pow(n.x, 2) + pow(n.y, 2) + 1);
	n.x *= norm;
	n.y *= norm;
	n.z = -norm;
	// c = 0 -> n = (0, 0, +1)
	return (n);
}
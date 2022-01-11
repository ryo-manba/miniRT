/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_bumpfunc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 02:22:27 by corvvs            #+#    #+#             */
/*   Updated: 2022/01/12 02:38:31 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static double	grayscale_color_at(
	t_img *image,
	int x,
	int y
)
{
	const unsigned int	color = mr_mlx_pixel_get(image, x, y);

	return ((color & 0xff) / 255.0);
}

static	void	uv_normal(
	t_vec3 *n,
	t_img *bumpmap,
	double i,
	double j
)
{
	const double	h1 = grayscale_color_at(bumpmap,
						(int)j, (int)i);
	const double	h2 = grayscale_color_at(bumpmap,
						(int)(j + 1) % bumpmap->width,
						(int)i);
	const double	h3 = grayscale_color_at(bumpmap,
						(int)j, (int)(i + 1) % bumpmap->height);
	const double	h4 = grayscale_color_at(bumpmap,
						(int)(j + 1) % bumpmap->width,
						(int)(i + 1) % bumpmap->height);
	const double	c = 2;

	n->x = c * ((h1 - h2 - h3 + h4) * (i - floor(i)) + (h2 - h4));
	n->y = c * ((h1 - h2 - h3 + h4) * (j - floor(j)) + (h3 - h4));
}

t_vec3	rt_bumpnormal(double u, double v, t_img *bumpmap)
{
	const double	jd = fmod(u * bumpmap->width + 100000 * bumpmap->width,
		bumpmap->width);
	const double	id = fmod(v * bumpmap->height + 100000 * bumpmap->height,
		bumpmap->height);
	t_vec3			n;
	double			norm;

	uv_normal(&n, bumpmap, id, jd);
	norm = -1 / sqrt(pow(n.x, 2) + pow(n.y, 2) + 1);
	n.x *= norm;
	n.y *= norm;
	n.z = -norm;
	return (n);
}

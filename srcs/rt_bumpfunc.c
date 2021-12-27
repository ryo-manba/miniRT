/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_bumpfunc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 02:22:27 by corvvs            #+#    #+#             */
/*   Updated: 2021/12/27 17:30:18 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#define IMAGE_W 6
#define IMAGE_H 6
static const double g_bumpmap[IMAGE_H][IMAGE_W] = {
	{0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
	{0.0, 0.3, 0.6, 0.6, 0.3, 0.0},
	{0.0, 0.6, 0.9, 0.9, 0.6, 0.0},
	{0.0, 0.6, 0.9, 0.9, 0.6, 0.0},
	{0.0, 0.3, 0.6, 0.6, 0.3, 0.0},
	{0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
};

t_vec3	test_bumpfunc_image(double u, double v)
{
	const double delta = 0.5;

	double jd = fmod(u / delta + 100000 * IMAGE_W, IMAGE_W);
	double id = fmod(v / delta + 100000 * IMAGE_H, IMAGE_H);
	int ji = jd;
	int ii = id;
	const double	h1 = g_bumpmap[ii][ji];
	const double	h2 = g_bumpmap[ii][(ji + 1) % IMAGE_W];
	const double	h3 = g_bumpmap[(ii + 1) % IMAGE_H][ji];
	const double	h4 = g_bumpmap[(ii + 1) % IMAGE_H][(ji + 1) % IMAGE_W];
	const double	ru = jd - (double)ji;
	const double	rv = id - (double)ii;
	const double	c = 5e-1;
	double			norm;
	t_vec3			n;
	n.x = c * ((h1 - h2 - h3 + h4) * rv + (h2 - h4));
	n.y = c * ((h1 - h2 - h3 + h4) * ru + (h3 - h4));
	norm = -1 / sqrt(pow(n.x, 2) + pow(n.y, 2) + 1);
	n.x *= norm;
	n.y *= norm;
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
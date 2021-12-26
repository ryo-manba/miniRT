/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_bumpfunc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 02:22:27 by corvvs            #+#    #+#             */
/*   Updated: 2021/12/27 02:23:27 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
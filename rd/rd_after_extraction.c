/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_after_extraction.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 20:59:37 by corvvs            #+#    #+#             */
/*   Updated: 2022/01/17 02:24:04 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rd_read.h"

static void	after_extraction_paraboloid(t_element *el)
{
	const t_vec3	fc = mr_vec3_sub(el->focalpoint, el->position);
	const t_vec3	n0 = el->direction;

	if (mr_vec3_dot(fc, el->direction) < 0)
		el->direction = mr_vec3_mul_double(&n0, -1);
}

static void	after_extraction_pyramidlight(t_element *el)
{
	const t_vec3	dy = {0, 1, 0};
	const double	t = mr_vec3_dot(dy, el->direction);
	t_vec3			dv0;
	t_vec3			du0;

	if (t > 0)
		dv0 = mr_vec3_sub(dy, mr_vec3_mul_double(&el->direction, t));
	else
		dv0 = (t_vec3){1, 0, 0};
	mr_normalize_comp(&dv0);
	du0 = mr_vec3_cross(&dv0, &el->direction);
	el->direction_u = mr_rot_around_axis(&du0, &el->direction, el->role);
	el->direction_v = mr_rot_around_axis(&dv0, &el->direction, el->role);
}

static void	after_extraction_light(t_element *el)
{
	el->color = mr_vec3_mul_double(&el->color, el->ratio);
	if (el->etype == RD_ET_PYRAMIDLIGHT)
		after_extraction_pyramidlight(el);
}

void	rt_after_extraction(t_element *el)
{
	double	r;

	el->radius = el->diameter / 2;
	r = mr_vec3_length(&el->direction);
	if (r == 0)
		r = 1;
	el->direction = mr_vec3_mul_double(&el->direction, 1 / r);
	el->color = mr_vec3_mul_double(&el->color, 1 / 255.0);
	el->subcolor = mr_vec3_mul_double(&el->subcolor, 1 / 255.0);
	if (el->etype == RD_ET_CONE && fabs(el->fov - 180) < 1e-6)
		el->etype = RD_ET_PLANE;
	el->fov *= M_PI / 360;
	el->fov2 *= M_PI / 360;
	el->role *= M_PI / 180;
	if (!el->gloss)
		el->gloss = 30;
	if (!el->k_diffuse)
		el->k_diffuse = 1;
	if (!el->k_specular)
		el->k_specular = 1;
	if (el->etype == RD_ET_PARABOLOID)
		after_extraction_paraboloid(el);
	if (el->etype == RD_ET_LIGHT || el->etype == RD_ET_SPOTLIGHT
		|| el->etype == RD_ET_PYRAMIDLIGHT || el->etype == RD_ET_SUNLIGHT)
		after_extraction_light(el);
}

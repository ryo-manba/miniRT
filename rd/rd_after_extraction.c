/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_after_extraction.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 20:59:37 by corvvs            #+#    #+#             */
/*   Updated: 2022/01/08 17:35:13 by corvvs           ###   ########.fr       */
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

static void	after_extraction_light(t_element *el)
{
	el->color = mr_vec3_mul_double(&el->color, el->ratio);
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
	if (el->etype == RD_ET_PARABOLOID)
		after_extraction_paraboloid(el);
	if (el->etype == RD_ET_LIGHT || el->etype == RD_ET_SPOTLIGHT)
		after_extraction_light(el);
}

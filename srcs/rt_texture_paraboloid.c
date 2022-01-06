/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_texture_paraboloid.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 13:41:07 by rmatsuka          #+#    #+#             */
/*   Updated: 2022/01/05 21:21:55 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void set_tangent_coordinate_paraboloid(t_hit_record *rec)
{
	const t_vec3	pc = mr_vec3_sub(rec->p, rec->element.focalpoint);
	t_vec3	E = mr_vec3_sub(rec->element.position, rec->element.focalpoint);
	t_vec3	N = rec->element.direction;
	if (mr_vec3_dot(E, rec->element.direction) >= 0)
		N = mr_vec3_mul_double(&N, -1);
	const t_vec3	w0 = rt_coord_perpendicular_unit(&N);
	const t_vec3	u0 = rt_coord_turn_around_90(&w0, &N);
	const double	d = -mr_vec3_dot(N, E);
	t_vec3			xx = mr_vec3_cross(&pc, &N);
	const double	x0 = mr_vec3_length(&xx);
	const double	xd = x0 / d;

	rec->u = 1 - (atan2(
			mr_vec3_dot(pc, w0),
			mr_vec3_dot(pc, u0)
		) / (2 * M_PI) - 0.5);
	rec->v = d * 0.5 * (xd * sqrt(1 + xd * xd) + log(sqrt(1 + xd * xd) + xd));
}

void	rt_set_tangent_paraboloid(
	t_hit_record *rec
)
{
	t_vec3	E = mr_vec3_sub(rec->element.position, rec->element.focalpoint);
	t_vec3	N = rec->element.direction;
	if (mr_vec3_dot(E, rec->element.direction) >= 0)
		N = mr_vec3_mul_double(&N, -1);
	rec->normal = mr_vec3_sub(rec->element.focalpoint, rec->p);
	rec->normal = mr_vec3_add(mr_unit_vector(&rec->normal), N);
	rec->normal = mr_unit_vector(&rec->normal);
	rec->w0 = rec->normal;
	rec->u0 = mr_vec3_cross(&N, &rec->w0);
	if (mr_vec3_length_squared(&rec->w0) == 0)
		rec->u0 = rt_coord_perpendicular_unit(&N);
	else
		rec->u0 = mr_unit_vector(&rec->u0);
	rec->v0 = mr_vec3_cross(&rec->w0, &rec->u0);
	if (rec->element.bump_el || rec->element.tex_el)
		set_tangent_coordinate_paraboloid(rec);
}

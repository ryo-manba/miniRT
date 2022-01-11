/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_texture_cylinder.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 13:41:07 by rmatsuka          #+#    #+#             */
/*   Updated: 2022/01/12 04:27:27 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	set_tangent_coordinate_cylinder(t_hit_record *rec)
{
	const t_vec3	pc = mr_vec3_sub(rec->p, rec->element.position);
	const t_vec3	v0 = rec->element.direction;
	const t_vec3	w0 = rt_coord_perpendicular_unit(&v0);
	const t_vec3	u0 = rt_coord_turn_around_90(&w0, &v0);

	rec->u = -atan2(mr_vec3_dot(pc, w0), mr_vec3_dot(pc, u0)) / (2 * M_PI);
	rec->v = -mr_vec3_dot(pc, v0);
}

void	rt_set_tangent_cylinder(
	t_hit_record *rec
)
{
	const t_vec3	axial_center = mr_vec3_add(
		rec->element.position,
		mr_vec3_mul_double(
			&rec->element.direction,
			rec->normal.x
		)
	);

	rec->normal = mr_vec3_sub(rec->p, axial_center);
	mr_normalize_comp(&rec->normal);
	rec->w0 = rec->normal;
	rec->v0 = rec->element.direction;
	rec->u0 = mr_vec3_cross(&rec->v0, &rec->w0);
	if (rec->element.bump_el || rec->element.tex_el)
		set_tangent_coordinate_cylinder(rec);
}

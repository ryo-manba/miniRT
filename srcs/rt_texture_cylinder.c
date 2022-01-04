/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_texture_cylinder.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 13:41:07 by rmatsuka          #+#    #+#             */
/*   Updated: 2022/01/03 23:37:03 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void set_tangent_coordinate_cylinder(t_hit_record *rec)
{
	const t_vec3	pc = mr_vec3_sub(rec->p, rec->element.position);
	const t_vec3	u0 = rt_coord_perpendicular_unit(&rec->element.direction);
	const t_vec3	v0 = rec->element.direction;

	rec->u = mr_vec3_dot(pc, u0);
	rec->v = mr_vec3_dot(pc, v0);
}

void	rt_set_tangent_cylinder(
	t_hit_record *rec
)
{
	t_vec3 axial_center = mr_vec3_add(
		rec->element.position,
		mr_vec3_mul_double(
			&rec->element.direction,
			rec->normal.x
		)
	);
	rec->normal = mr_vec3_sub(rec->p, axial_center);
	rec->normal = mr_unit_vector(&rec->normal);
	rec->w0 = rec->normal;
	rec->u0 = rec->element.direction;
	rec->v0 = mr_vec3_cross(&rec->w0, &rec->u0);
	if (rec->element.bump_el || rec->element.tex_el)
		set_tangent_coordinate_cylinder(rec);
}

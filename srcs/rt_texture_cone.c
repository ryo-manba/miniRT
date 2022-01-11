/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_texture_cone.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 23:37:49 by corvvs            #+#    #+#             */
/*   Updated: 2022/01/12 04:21:53 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	set_tangent_coordinate_cone(t_hit_record *rec)
{
	const t_vec3	pc = mr_vec3_sub(rec->p, rec->element.position);
	const t_vec3	u1 = rt_coord_perpendicular_unit(&rec->element.direction);
	const t_vec3	u2 = rt_coord_turn_around_90(&u1, &rec->element.direction);
	const double	dx = mr_vec3_dot(pc, u1);
	const double	dz = mr_vec3_dot(pc, u2);

	rec->u = -atan2(dz, dx) / (2 * M_PI);
	rec->v = mr_vec3_length(&pc);
}

void	rt_set_tangent_cone(
	t_hit_record *rec
)
{
	rec->v0 = mr_vec3_sub(rec->p, rec->element.position);
	rec->normal = mr_vec3_sub(
			rec->v0,
			mr_vec3_mul_double(&rec->element.direction,
				pow(mr_vec3_length(&rec->v0), 2) / \
				mr_vec3_dot(rec->v0, rec->element.direction))
			);
	mr_normalize_comp(&rec->normal);
	rec->w0 = rec->normal;
	mr_normalize_comp(&rec->v0);
	rec->u0 = mr_vec3_cross(&rec->v0, &rec->w0);
	if (rec->element.bump_el || rec->element.tex_el)
		set_tangent_coordinate_cone(rec);
}

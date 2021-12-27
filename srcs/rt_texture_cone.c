/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_texture_cone.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 23:37:49 by corvvs            #+#    #+#             */
/*   Updated: 2021/12/27 15:28:10 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3 test_bumpmap_cone(t_hit_record *rec)
{
	const t_vec3	pc = mr_vec3_sub(rec->p, rec->element.position);
	const t_vec3	u1 = rt_coord_perpendicular_unit(&rec->element.direction);
	const t_vec3	u2 = rt_coord_turn_around_90(&u1, &rec->element.direction);
	const double	dx = mr_vec3_dot(pc, u1);
	const double	dz = mr_vec3_dot(pc, u2);

	return (test_bumpfunc_image(atan2(dz, dx) * 12, mr_vec3_length(&pc) * 4));
}

void	rt_set_tangent_cone(
	t_hit_record *rec
)
{
	const t_vec3 pc = mr_vec3_sub(rec->p, rec->element.position);

	rec->normal = mr_vec3_sub(
		pc,
		mr_vec3_mul_double(&rec->element.direction,
			pow(mr_vec3_length(&pc), 2) / mr_vec3_dot(pc, rec->element.direction))
	);
	rec->normal = mr_unit_vector(&rec->normal);
	rec->w0 = rec->normal;
	rec->v0 = mr_unit_vector(&pc);
	rec->u0 = mr_vec3_cross(&rec->v0, &rec->w0);
	rec->normal = test_bumpmap_cone(rec);
	rec->normal = rt_vec_tangent_to_global(rec, &rec->normal);
}

void	rt_texture_cone(t_hit_record *rec, const t_element *el)
{
	const t_vec3	r = mr_vec3_sub(rec->p, el->position);
	const double	phi = mr_vec3_dot(el->direction, r);
	const t_vec3	u1 = rt_coord_perpendicular_unit(&el->direction);
	const t_vec3	u2 = rt_coord_turn_around_90(&u1, &el->direction);
	const double	dx = mr_vec3_dot(r, u1);
	const double	dz = mr_vec3_dot(r, u2);
	const double	theta = atan2(dz, dx);

	rec->tex.u = theta / M_PI;
	rec->tex.v = phi / (2 * M_PI);
}

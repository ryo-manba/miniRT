/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_texture_cone.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 23:37:49 by corvvs            #+#    #+#             */
/*   Updated: 2021/12/27 00:18:48 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3 test_bumpmap_cone(t_hit_record *rec)
{

	
	const t_vec3	pc = mr_vec3_sub(rec->p, rec->element.position);
	const t_vec3	u1 = rt_coord_perpendicular_unit(&rec->element.direction);
	const t_vec3	u2 = rt_coord_turn_around_90(&u1, &rec->element.direction);
	const double	c = 2e-1;
	const double	dx = mr_vec3_dot(pc, u1);
	const double	dz = mr_vec3_dot(pc, u2);
	const double	u = atan2(dz, dx) * 14;
	const double	v = mr_vec3_length(&pc) * 40;
	double	norm;
	t_vec3	n;
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

void	rt_set_tangent_cone(
	t_hit_record *rec
)
{
	const t_vec3 pc = mr_vec3_sub(rec->p, rec->element.position);

	rec->normal = mr_vec3_sub(
		pc,
		mr_vec3_mul_double(&rec->element.direction, pow(mr_vec3_length(&pc), 2) / mr_vec3_dot(pc, rec->element.direction))
	);
	rec->normal = mr_unit_vector(&rec->normal);
	rec->w0 = rec->normal;
	rec->v0 = mr_unit_vector(&pc);
	rec->u0 = mr_vec3_cross(&rec->v0, &rec->w0);
	// t_vec3 vt = {0, 0, 1};
	// printf("n1: "); vec3_debug(&rec->normal);
	// rec->normal = rt_vec_tangent_to_global(rec, &vt);
	// printf("n2: "); vec3_debug(&rec->normal);
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

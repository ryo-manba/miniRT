/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_texture_plane.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 13:30:58 by rmatsuka          #+#    #+#             */
/*   Updated: 2021/12/26 23:30:57 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3 test_bumpmap_plane(t_hit_record *rec)
{

	
	const t_vec3	pc = mr_vec3_sub(rec->p, rec->element.position);
	const double	c = 5e-1;
	const double	u = mr_vec3_dot(pc, rec->u0) * 4;
	const double	v = mr_vec3_dot(pc, rec->v0) * 5;
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

void	rt_set_tangent_plane(
	t_hit_record *rec
)
{
	rec->normal = rec->element.direction;
	rec->w0 = rec->element.direction;
	rec->u0 = rt_coord_perpendicular_unit(&rec->w0);
	rec->v0 = rt_coord_turn_around_90(&rec->u0, &rec->w0);
	// t_vec3 vt = {0, 0, 1};
	// rec->normal = rt_vec_tangent_to_global(rec, &vt);
	rec->normal = test_bumpmap_plane(rec);
	rec->normal = rt_vec_tangent_to_global(rec, &rec->normal);
}

void	rt_texture_plane(t_hit_record *rec)
{
	const t_vec3	p1 = rt_coord_perpendicular_unit(&rec->normal);
	const t_vec3	p2 = rt_coord_turn_around_90(&p1, &rec->normal);

	rec->tex.u = mr_vec3_dot(mr_vec3_sub(rec->p, rec->element.position), p1);
	rec->tex.v = mr_vec3_dot(mr_vec3_sub(rec->p, rec->element.position), p2);
}

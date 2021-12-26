/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_texture_plane.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 13:30:58 by rmatsuka          #+#    #+#             */
/*   Updated: 2021/12/27 02:57:40 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3 test_bumpmap_plane(t_hit_record *rec)
{
	const t_vec3	pc = mr_vec3_sub(rec->p, rec->element.position);
	const double	u = mr_vec3_dot(pc, rec->u0) * 4;
	const double	v = mr_vec3_dot(pc, rec->v0) * 5;

	return (test_bumpfunc_wave2(u, v));
}

void	rt_set_tangent_plane(
	t_hit_record *rec
)
{
	rec->normal = rec->element.direction;
	rec->w0 = rec->element.direction;
	rec->u0 = rt_coord_perpendicular_unit(&rec->w0);
	rec->v0 = rt_coord_turn_around_90(&rec->u0, &rec->w0);
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

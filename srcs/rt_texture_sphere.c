/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_texture_sphere.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 13:39:11 by rmatsuka          #+#    #+#             */
/*   Updated: 2021/12/26 23:30:02 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3 test_bumpmap_sphere(t_hit_record *rec)
{
	const double	c = 5e-1;
	const double	u = atan2(rec->p.x - rec->element.position.x, rec->p.z - rec->element.position.z) * 50;
	const double	v = acos((rec->p.y - rec->element.position.y) / rec->element.radius) * 0.5;
	double	norm;
	t_vec3	n;
	n.x = c * cos(u) * sin(v);
	n.y = c * sin(u) * cos(v);
	n.z = -1;
	norm = -1 / sqrt(pow(n.x, 2) + pow(n.y, 2) + 1);
	n.x *= norm;
	n.y *= norm;
	n.z *= norm;
	return (n);
}

void	rt_set_tangent_sphere(
	t_hit_record *rec
)
{
	const t_vec3	y0 = {0, 1, 0};

	rec->normal = mr_vec3_sub(rec->p, rec->element.position);
	rec->normal = mr_unit_vector(&rec->normal);
	rec->w0 = rec->normal;
	rec->u0 = mr_vec3_cross(&rec->w0, &y0);
	rec->u0 = mr_unit_vector(&rec->u0);
	rec->v0 = mr_vec3_cross(&rec->w0, &rec->u0);
	// t_vec3 vt = {0, 0, 1};
	// rec->normal = rt_vec_tangent_to_global(rec, &vt);
	rec->normal = test_bumpmap_sphere(rec);
	rec->normal = rt_vec_tangent_to_global(rec, &rec->normal);
}

void	rt_texture_sphere(t_hit_record *rec)
{
	const double	theta = atan2(rec->normal.x, rec->normal.z);
	const double	phi = acos(rec->normal.y);

	rec->tex.u = 1 - (theta / M_PI);
	rec->tex.v = 1 - (phi / M_PI);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_texture_sphere.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 13:39:11 by rmatsuka          #+#    #+#             */
/*   Updated: 2021/12/31 18:50:07 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void test_bumpmap_sphere(t_hit_record *rec)
{
	const t_vec3	*pos = &rec->element.position;
	rec->u = atan2(rec->p.x - pos->x, rec->p.z - pos->z);
	rec->v = acos((rec->p.y - pos->y) / rec->element.radius);
}

void	rt_set_tangent_sphere(
	t_hit_record *rec
)
{
	const t_vec3	y0 = Y0;

	rec->normal = mr_vec3_sub(rec->p, rec->element.position);
	rec->normal = mr_unit_vector(&rec->normal);
	rec->w0 = rec->normal;
	rec->u0 = mr_vec3_cross(&rec->w0, &y0);
	rec->u0 = mr_unit_vector(&rec->u0);
	rec->v0 = mr_vec3_cross(&rec->w0, &rec->u0);
	if (rec->element.bumpmap || rec->element.texture)
		test_bumpmap_sphere(rec);
	if (rec->element.bumpmap)
		rec->normal = test_bumpfunc_image(rec->u, rec->v, rec->element.bumpmap);
	else
		rec->normal = Z0;
	rec->normal = rt_vec_tangent_to_global(rec, &rec->normal);
	if (rec->element.texture)
		rec->color = rt_element_color(rec->u, rec->v, &rec->element);
	else
		rec->color = rec->element.color;
}

void	rt_texture_sphere(t_hit_record *rec)
{
	const double	theta = atan2(rec->normal.x, rec->normal.z);
	const double	phi = acos(rec->normal.y);

	rec->tex.u = 1 - (theta / M_PI);
	rec->tex.v = 1 - (phi / M_PI);
}

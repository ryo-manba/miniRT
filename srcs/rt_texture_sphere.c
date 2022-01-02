/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_texture_sphere.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 13:39:11 by rmatsuka          #+#    #+#             */
/*   Updated: 2022/01/02 13:54:25 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void set_tangent_coordinate_sphere(t_hit_record *rec)
{
	const t_vec3	*pos = &rec->element.position;
	rec->u = 1 - (atan2(rec->p.x - pos->x, rec->p.z - pos->z) / (2 * M_PI) - 0.5);
	rec->v = acos((rec->p.y - pos->y) / rec->element.radius) / (M_PI);
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
		set_tangent_coordinate_sphere(rec);
}

void	rt_texture_sphere(t_hit_record *rec)
{
	const double	theta = atan2(rec->normal.x, rec->normal.z);
	const double	phi = acos(rec->normal.y);

	rec->tex.u = 1 - (theta / M_PI);
	rec->tex.v = 1 - (phi / M_PI);
}

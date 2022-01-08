/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_texture_sphere.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 13:39:11 by rmatsuka          #+#    #+#             */
/*   Updated: 2022/01/08 15:34:00 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	set_tangent_coordinate_sphere(t_hit_record *rec)
{
	const t_vec3	*pos = &rec->element.position;

	rec->u = 1 - (
			atan2(rec->p.x - pos->x, rec->p.z - pos->z) / (2 * M_PI) - 0.5);
	rec->v = acos((rec->p.y - pos->y) / rec->element.radius) / (M_PI);
}

void	rt_set_tangent_sphere(
	t_hit_record *rec
)
{
	const t_vec3	y0 = (t_vec3){0, 1, 0};

	rec->normal = mr_vec3_sub(rec->p, rec->element.position);
	mr_normalize_comp(&rec->normal);
	rec->w0 = rec->normal;
	rec->u0 = mr_vec3_cross(&rec->w0, &y0);
	mr_normalize_comp(&rec->u0);
	rec->v0 = mr_vec3_cross(&rec->w0, &rec->u0);
	if (rec->element.bump_el || rec->element.tex_el)
		set_tangent_coordinate_sphere(rec);
}

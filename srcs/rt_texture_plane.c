/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_texture_plane.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 13:30:58 by rmatsuka          #+#    #+#             */
/*   Updated: 2022/01/02 18:21:18 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void set_tangent_coordinate_plane(t_hit_record *rec)
{
	const t_vec3	pc = mr_vec3_sub(rec->p, rec->element.position);

	rec->u = mr_vec3_dot(pc, rec->u0);
	rec->v = mr_vec3_dot(pc, rec->v0);
}

void	rt_set_tangent_plane(
	t_hit_record *rec
)
{
	rec->normal = rec->element.direction;
	rec->w0 = rec->element.direction;
	rec->u0 = rt_coord_perpendicular_unit(&rec->w0);
	rec->v0 = rt_coord_turn_around_90(&rec->u0, &rec->w0);
	if (rec->element.bumpmap || rec->element.texture)
		set_tangent_coordinate_plane(rec);
}

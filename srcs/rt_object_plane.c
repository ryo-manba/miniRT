/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_object_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 20:14:54 by corvvs            #+#    #+#             */
/*   Updated: 2021/12/26 23:30:52 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// 接空間上のベクトルを通常空間に変換する
t_vec3	rt_vec_tangent_to_global(
	t_hit_record *rec,
	t_vec3 *vtangent
)
{
	t_vec3	vglobal;

	vglobal.x = rec->u0.x * vtangent->x
		+ rec->v0.x * vtangent->y
		+ rec->w0.x * vtangent->z;
	vglobal.y = rec->u0.y * vtangent->x
		+ rec->v0.y * vtangent->y
		+ rec->w0.y * vtangent->z;
	vglobal.z = rec->u0.z * vtangent->x
		+ rec->v0.z * vtangent->y
		+ rec->w0.z * vtangent->z;
	return (vglobal);
}

bool	rt_hittest_plane(
	const t_element *el,
	const t_ray *ray,
	t_hit_record *rec)
{
	const t_vec3	oc = mr_vec3_sub(el->position, ray->origin);
	const double	den = mr_vec3_dot(oc, el->direction);
	const double	num = mr_vec3_dot(ray->direction, el->direction);

	if (num == 0)
		return (false);
	rec->t = den / num;
	rec->p = rt_hit_point(rec->t, ray);
	if (rec->t < 1)
		return (false);
	rec->hit = true;
	rt_texture_plane(rec);
	rt_after_hit(el, ray, rec);
	return (true);
}

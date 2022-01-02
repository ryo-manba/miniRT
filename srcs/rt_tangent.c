/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_tangent.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 13:52:57 by corvvs            #+#    #+#             */
/*   Updated: 2022/01/02 13:53:03 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static const t_object_tangent_setter g_tangent_setters[] = {
	NULL,
	NULL,
	NULL,
	NULL,
	rt_set_tangent_sphere,
	rt_set_tangent_plane,
	rt_set_tangent_cylinder,
	rt_set_tangent_cone,
};

void	rt_set_tangent_space(
	t_hit_record *rec
)
{
	g_tangent_setters[rec->element.etype](rec);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_tangent.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 13:52:57 by corvvs            #+#    #+#             */
/*   Updated: 2022/01/14 22:57:11 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static const t_object_tangent_setter	g_tangent_setters[] = {
	NULL,
	NULL,
	NULL,
	NULL,
	rt_set_tangent_sphere,
	rt_set_tangent_plane,
	rt_set_tangent_cylinder,
	rt_set_tangent_paraboloid,
	rt_set_tangent_cone,
};

/** m_freq:
 *  plane    :  0.5
 *  cylinder : 10.0
 *  sphere   : 10.0
 */
static t_vec3	rt_color_checker(const t_hit_record *rec)
{
	const double	u = rec->u;
	const double	v = rec->v;
	const t_element	*el = rec->element.tex_el;
	const int		sines = \
			(int)(rt_floor(el->freq_u * u * 2) + rt_floor(el->freq_v * v * 2));

	if (sines % 2 == 0)
	{
		return (el->color);
	}
	else
	{
		return (el->subcolor);
	}
}

void	rt_set_tangent_space(
	t_hit_record *rec
)
{
	g_tangent_setters[rec->element.etype](rec);
	if (rec->element.bump_el && rec->element.bump_el->image)
		rec->normal = rt_bumpnormal(rec->u, rec->v, rec->element.bump_el);
	else
		rec->normal = (t_vec3){0, 0, 1};
	rec->normal = rt_vec_tangent_to_global(rec, &rec->normal);
	if (rec->element.tex_el && rec->element.tex_el->etype == RD_ET_TEXTURE)
		rec->color = rt_color_image(rec->u, rec->v, rec->element.tex_el);
	else if (rec->element.tex_el && rec->element.tex_el->etype == RD_ET_CHECKER)
		rec->color = rt_color_checker(rec);
	else
		rec->color = rec->element.color;
}

// transform a vector `vtangent` on tangent space
// into global space.
t_vec3	rt_vec_tangent_to_global(
	t_hit_record *rec,
	const t_vec3 *vtangent
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_texture_paraboloid.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 13:41:07 by rmatsuka          #+#    #+#             */
/*   Updated: 2022/01/08 15:33:38 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static double	tangent_u(
	const t_element *el,
	const t_vec3 *pc
)
{
	const t_vec3	w0 = rt_coord_perpendicular_unit(&el->direction);
	const t_vec3	u0 = rt_coord_turn_around_90(&w0, &el->direction);

	return (1 - (atan2(
				mr_vec3_dot(*pc, w0),
				mr_vec3_dot(*pc, u0)
			) / (2 * M_PI) - 0.5));
}

static double	tangent_v(
	const t_element *el,
	const t_vec3 *pc
)
{
	const t_vec3	E = mr_vec3_sub(el->position, el->focalpoint);
	const double	d = -mr_vec3_dot(el->direction, E);
	const t_vec3	xx = mr_vec3_cross(pc, &el->direction);
	const double	xd = mr_vec3_length(&xx) / d;

	return (d * 0.5 * (xd * sqrt(1 + xd * xd) + log(sqrt(1 + xd * xd) + xd)));
}

static void	set_tangent_coordinate_paraboloid(t_hit_record *rec)
{
	const t_element	*el = &rec->element;
	const t_vec3	pc = mr_vec3_sub(rec->p, el->focalpoint);

	rec->u = tangent_u(el, &pc);
	rec->v = tangent_v(el, &pc);
}

void	rt_set_tangent_paraboloid(
	t_hit_record *rec
)
{
	const t_element	*el = &rec->element;

	rec->normal = mr_vec3_sub(rec->element.focalpoint, rec->p);
	mr_normalize_comp(&rec->normal);
	mr_vec3_add_comp(&rec->normal, el->direction);
	mr_normalize_comp(&rec->normal);
	rec->w0 = rec->normal;
	rec->u0 = mr_vec3_cross(&el->direction, &rec->w0);
	if (mr_vec3_length_squared(&rec->w0) == 0)
		rec->u0 = rt_coord_perpendicular_unit(&el->direction);
	else
		mr_normalize_comp(&rec->u0);
	rec->v0 = mr_vec3_cross(&rec->w0, &rec->u0);
	if (rec->element.bump_el || rec->element.tex_el)
		set_tangent_coordinate_paraboloid(rec);
}

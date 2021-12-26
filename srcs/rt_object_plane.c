/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_object_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 20:14:54 by corvvs            #+#    #+#             */
/*   Updated: 2021/12/25 21:18:54 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
	rec->normal = el->direction;
	rec->hit = true;
	rt_texture_plane(rec);
	rt_after_hit(el, ray, rec);
	return (true);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_object_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 20:13:53 by corvvs            #+#    #+#             */
/*   Updated: 2021/12/25 17:16:17 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	rt_hittest_sphere(
	const t_element *el,
	const t_ray *ray,
	t_hit_record *rec)
{
	const t_vec3	oc = mr_vec3_sub(ray->origin, el->position);
	t_equation2	eq;

	eq.a = mr_vec3_length_squared(&ray->direction);
	eq.b_half = mr_vec3_dot(oc, ray->direction);
	eq.c = mr_vec3_length_squared(&oc) - el->radius * el->radius;
	if (rt_solve_equation2(&eq) < 1)
		return (false);
	rec->t = 0;
	if (eq.t1 >= 1)
		rec->t = eq.t1;
	else if (eq.t2 >= 1)
		rec->t = eq.t2;
	else
		return (false);
	rec->p = rt_hit_point(rec->t, ray);
	rec->hit = true;
	rec->normal = mr_vec3_sub(rec->p, el->position);
	rec->normal = mr_unit_vector(&rec->normal);

	// !!BONUS
	double theta = atan2(rec->normal.x, rec->normal.z);
	double phi = acos(rec->normal.y / M_PI);

	rec->tex.u = 1 - ((theta / (M_PI * 2) + 0.5));
	rec->tex.v = 1 - ((phi / M_PI));

	rt_after_hit(el, ray, rec);
	return (true);
}

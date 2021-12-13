/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_object_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatsuka < rmatsuka@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 20:13:53 by corvvs            #+#    #+#             */
/*   Updated: 2021/12/13 16:37:11 by rmatsuka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	rt_hittest_sphere(
	const t_element *el,
	const t_ray *ray,
	t_hit_record *rec)
{
	const t_vec3	oc = mr_vec3_sub(ray->origin, el->position);
	const double	a = mr_vec3_length_squared(&ray->direction);
	const double	half_b = mr_vec3_dot(oc, ray->direction);
	const double	c = mr_vec3_length_squared(&oc) - el->radius * el->radius;
	const double	discriminant = half_b * half_b - a * c;

	if (discriminant < 0)
		return (false);
	double root = sqrt(discriminant);
	rec->t = 0;
	if (((-half_b - root) / a) >= 1)
		rec->t = (-half_b - root) / a;
	else if (((-half_b + root) / a) >= 1)
		rec->t = (-half_b + root) / a;
	else
		return (false);
	rec->p = rt_hit_point(rec->t, ray);
	rec->hit = true;
	rec->normal = mr_vec3_sub(rec->p, el->position);
	rec->normal = mr_unit_vector(&rec->normal);

	// !!BONUS
	double theta = atan2(rec->normal.x, rec->normal.z);
	double phi = acos(rec->normal.y);

	rec->tex.u = 1 - ((theta / (M_PI * 2) + 0.5));
	rec->tex.v = 1 - ((phi / M_PI));

	rt_after_hit(el, ray, rec);
	return (true);
}

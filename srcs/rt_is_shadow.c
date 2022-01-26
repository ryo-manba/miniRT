/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_is_shadow.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 16:56:38 by rmatsuka          #+#    #+#             */
/*   Updated: 2022/01/20 09:37:30 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#define EPS 1e-5
#define EPS2 1e-2

static bool	is_in_pyramid_light(
	const t_element *light,
	const t_vec3 *q)
{
	const t_vec3	ru = mr_vec3_sub(*q,
		mr_vec3_mul_double(&light->direction_v,
			mr_vec3_dot(*q, light->direction_v)));
	const t_vec3	rv = mr_vec3_sub(*q,
		mr_vec3_mul_double(&light->direction_u,
			mr_vec3_dot(*q, light->direction_u)));

	if (mr_vec3_dot(light->direction, mr_unit_vector(&ru)) < cos(light->fov))
		return (false);
	if (mr_vec3_dot(light->direction, mr_unit_vector(&rv)) < cos(light->fov2))
		return (false);
	return (true);
}

// reflection will only happen when
// both light and camera are in same side to the surface
static bool	is_reflective_part(
	const t_hit_record *rec,
	const t_element *light,
	const t_ray *ray)
{
	t_vec3	light_in;
	double	cos_light;
	double	cos_ray;
	bool	is_reflective;
	t_vec3	pc;

	light_in = rt_get_incident_vector(rec, light);
	cos_light = mr_vec3_dot(light_in, rec->normal);
	cos_ray = mr_vec3_dot(ray->direction, rec->normal);
	is_reflective
		= ((cos_light > 0 && cos_ray > 0) || (cos_light < 0 && cos_ray < 0));
	if (!is_reflective)
		return (false);
	if (light->etype == RD_ET_SPOTLIGHT)
	{
		pc = mr_vec3_sub(rec->p, light->position);
		mr_normalize_comp(&pc);
		return (mr_vec3_dot(pc, light->direction) >= cos(light->fov));
	}
	if (light->etype == RD_ET_PYRAMIDLIGHT)
		return (is_in_pyramid_light(light, &light_in));
	return (true);
}

static bool	is_obj_closer_than_light(
	const t_subscene *subscene,
	const t_ray *shadow_ray,
	const double dist_to_light)
{
	size_t	i;
	double	dist_to_obj;

	ft_bzero(subscene->recs,
		subscene->info->scene->n_objects * sizeof(t_hit_record));
	i = 0;
	while (i < subscene->info->scene->n_objects)
	{
		if (rt_hit_object(subscene->info->scene->objects[i],
				shadow_ray, &subscene->recs[i]))
		{
			dist_to_obj = subscene->recs[i].t - 1;
			if (dist_to_obj < dist_to_light)
			{
				return (true);
			}
		}
		i += 1;
	}
	return (false);
}

bool	rt_is_shadowed_from(
	const t_hit_record *actual,
	const t_element *light,
	t_subscene *subscene,
	t_ray *ray)
{
	t_vec3	incident;
	double	dist_to_light;
	t_ray	shadow_ray;

	if (!is_reflective_part(actual, light, ray))
		return (true);
	incident = rt_get_incident_vector(actual, light);
	mr_vec3_mul_double_comp(&incident, -1);
	if (light->etype == RD_ET_SUNLIGHT)
		dist_to_light = rd_inf(true);
	else
		dist_to_light = 1;
	shadow_ray.origin = mr_vec3_add(
			actual->p, mr_vec3_mul_double(&incident, EPS - 1));
	shadow_ray.direction = incident;
	shadow_ray.for_shadow = true;
	shadow_ray.subpx = 1;
	if (is_obj_closer_than_light(subscene, &shadow_ray, dist_to_light))
		return (true);
	return (false);
}

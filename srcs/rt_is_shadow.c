/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_is_shadow.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 16:56:38 by rmatsuka          #+#    #+#             */
/*   Updated: 2022/01/17 01:52:37 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#define EPS 1e-5
#define EPS2 1e-2

static bool	is_in_pyramid_light(
	const t_hit_record *rec,
	const t_element *light)
{
	const t_vec3	q = mr_vec3_sub(rec->p, light->position);
	const t_vec3	ru = mr_vec3_sub(q,
		mr_vec3_mul_double(&light->direction_v,
			mr_vec3_dot(q, light->direction_v)));
	const t_vec3	rv = mr_vec3_sub(q,
		mr_vec3_mul_double(&light->direction_u,
			mr_vec3_dot(q, light->direction_u)));

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
	const t_vec3	light_in = mr_vec3_sub(rec->p, light->position);
	const double	cos_light = mr_vec3_dot(light_in, rec->normal);
	const double	cos_ray = mr_vec3_dot(
						ray->direction, rec->normal);
	const bool		is_reflective = ((cos_light > 0 && cos_ray > 0) \
								|| (cos_light < 0 && cos_ray < 0));
	t_vec3			pc;

	if (!is_reflective)
	{
		return (false);
	}
	if (light->etype == RD_ET_SPOTLIGHT)
	{
		pc = mr_vec3_sub(rec->p, light->position);
		mr_normalize_comp(&pc);
		return (mr_vec3_dot(pc, light->direction) >= cos(light->fov));
	}
	if (light->etype == RD_ET_PYRAMIDLIGHT)
		return (is_in_pyramid_light(rec, light));
	return (true);
}

static bool	is_obj_closer_than_light(
	const t_scene *scene,
	const t_ray *shadow_ray,
	const double dist_to_light)
{
	size_t	i;
	double	dist_to_obj;

	i = 0;
	while (i < scene->n_objects)
	{
		if (rt_hit_object(scene->objects[i], shadow_ray, &scene->recs[i]))
		{
			dist_to_obj = scene->recs[i].t - 1 + EPS;
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
	t_scene *scene,
	t_ray *ray)
{
	const t_vec3	v = mr_vec3_sub(light->position, actual->p);
	const t_vec3	incident = mr_vec3_mul_double(&v, 1);
	const double	dist_to_light = 1;
	t_ray			shadow_ray;

	if (!is_reflective_part(actual, light, ray))
	{
		ray->marking_color = (t_vec3){0, 0, 1};
		return (true);
	}
	shadow_ray.origin = mr_vec3_add(
			actual->p, mr_vec3_mul_double(&incident, EPS - 1));
	shadow_ray.direction = incident;
	shadow_ray.for_shadow = true;
	shadow_ray.subpx = 1;
	ft_bzero(scene->recs, scene->n_objects * sizeof(t_hit_record));
	if (is_obj_closer_than_light(scene, &shadow_ray, dist_to_light))
	{
		ray->marking_color = (t_vec3){1, 0, 1};
		return (true);
	}
	ray->marking_color = (t_vec3){1, 1, 0};
	return (false);
}

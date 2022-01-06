/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_is_shadow.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatsuka < rmatsuka@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 16:56:38 by rmatsuka          #+#    #+#             */
/*   Updated: 2022/01/05 11:12:36 by rmatsuka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#define EPS 1e-5
#define EPS2 1e-2

// 光源とカメラが反射面を挟んで逆側にいる時反射は起きない
static bool	is_reflective_part(
	const t_hit_record *rec,
	const t_element *light,
	const t_ray *ray)
{
	const t_vec3	light_in = mr_vec3_sub(rec->p, light->position);
	const double	cos_light = mr_vec3_dot(
						light_in, rec->normal);
	const double	cos_ray = mr_vec3_dot(
						ray->direction, rec->normal);
	const bool		is_reflective = ((cos_light > 0 && cos_ray > 0) \
								|| (cos_light < 0 && cos_ray < 0));
	t_vec3			pc;

	if (!is_reflective)
		return (false);
	if (light->etype != RD_ET_SPOTLIGHT)
		return (true);
	pc = mr_vec3_sub(rec->p, light->position);
	pc = mr_unit_vector(&pc);
	return (mr_vec3_dot(pc, light->direction) >= cos(light->fov * M_PI / 360));
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
			if (dist_to_obj < dist_to_light \
				|| fabs(dist_to_obj - dist_to_light) < EPS)
			{
				return (true);
			}
		}
		i += 1;
	}
	return (false);
}

// v = 交点から光源へのベクトル
// incident = 出射ベクトル
// shadow_ray.originを入射方向に少しずらす
// 物体との距離が光源よりも近い場合は影
bool	rt_is_shadow(
	const t_hit_record *actual,
	const t_element *light,
	t_scene *scene,
	t_ray *ray)
{
	const t_vec3	v = mr_vec3_sub(light->position, actual->p);
	const t_vec3	incident = mr_unit_vector(&v);
	const double	dist_to_light = mr_vec3_length(&v);
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
	ft_bzero(scene->recs, scene->n_objects * sizeof(t_hit_record));
	if (is_obj_closer_than_light(scene, &shadow_ray, dist_to_light))
	{
		ray->marking_color = (t_vec3){1, 0, 1};
		return (true);
	}
	ray->marking_color = (t_vec3){1, 1, 0};
	return (false);
}

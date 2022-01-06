/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_is_shadow.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 16:56:38 by rmatsuka          #+#    #+#             */
/*   Updated: 2022/01/05 00:27:50 by corvvs           ###   ########.fr       */
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
	const bool is_reflective = (cos_light > 0 && cos_ray > 0) || (cos_light < 0 && cos_ray < 0);

	if (!is_reflective)
		return (false);
	if (light->etype != RD_ET_SPOTLIGHT)
		return (true);
	t_vec3 pc = mr_vec3_sub(rec->p, light->position);
	pc = mr_unit_vector(&pc);
	const double cs = mr_vec3_dot(pc, light->direction);
	return (cs >= cos(light->fov * M_PI / 360));
}

bool	rt_is_shadow(
	const t_hit_record *actual,
	const t_element *light,
	t_scene *scene,
	t_ray *ray)
{
	const t_vec3 *light_pos = &light->position;
	if (!is_reflective_part(actual, light, ray))
	{
		ray->marking_color = (t_vec3){0,0,1};
		return (true);
	}
	const t_vec3	v = mr_vec3_sub(*light_pos, actual->p); // 交点から光源へのベクトル
	const t_vec3	incident = mr_unit_vector(&v); // 出射ベクトル
	const double	dist_to_light = mr_vec3_length(&v);
	t_ray			shadow_ray;
	size_t			i;

	shadow_ray.origin = mr_vec3_add(actual->p, mr_vec3_mul_double(&incident, EPS - 1)); // 入射方向に少しずらす
	shadow_ray.direction = incident;
	shadow_ray.for_shadow = true;
	ft_bzero(scene->recs, scene->n_objects * sizeof(t_hit_record));
	i = 0;
	while (i < scene->n_objects)
	{
		if (rt_hit_object(scene->objects[i], &shadow_ray, &scene->recs[i]))
		{
			double dist_to_obj = scene->recs[i].t - 1 + EPS;
			if (dist_to_obj < dist_to_light || fabs(dist_to_obj - dist_to_light) < EPS)  // 物体との距離が光源よりも近い場合
			{
				ray->marking_color = (t_vec3){1,0,1};
				return (true);
			}
		}
		i += 1;
	}
	ray->marking_color = (t_vec3){1,1,0};
	return (false);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_is_shadow.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 16:56:38 by rmatsuka          #+#    #+#             */
/*   Updated: 2021/12/25 23:28:35 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#define EPS 1e-6

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
	if (light->etype == RD_ET_SPOTLIGHT)
	{
		// [スポットライトの場合]
		// normalize(反射点 - ライト位置)・ライト方位 > cos(FOV/2)ならばfalse
		t_vec3 pc = mr_vec3_sub(rec->p, light->position);
		pc = mr_unit_vector(&pc);
		const double cs = mr_vec3_dot(pc, light->direction);
		printf("cs = %f\n", cs);
		if (cs < cos(light->fov * M_PI / 360))
			return (false);
	}
	return (is_reflective);
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
	t_ray	shadow_ray;
	const t_vec3 v = mr_vec3_sub(*light_pos, actual->p); // 交点から光源へのベクトル
	const t_vec3 incident = mr_unit_vector(&v); // 出射ベクトル
	shadow_ray.origin = mr_vec3_add(actual->p, mr_vec3_mul_double(&incident, EPS - 1)); // 入射方向に少しずらす
	shadow_ray.direction = incident;
	size_t i = 0;

	// 光源までの距離
	double dist_to_light = mr_vec3_length(&v) - EPS;

	ft_bzero(scene->recs, scene->n_objects * sizeof(t_hit_record));
	while (i < scene->n_objects)
	{
		if (rt_hit_object(scene->objects[i], &shadow_ray, &scene->recs[i]))
		{
			t_vec3 normal = shadow_ray.direction;
			t_vec3 tmp = mr_vec3_mul_double(&normal, scene->recs[i].t); // シャドウレイからt倍する
			double dist_to_obj = mr_vec3_length(&tmp) - 1;
			if (dist_to_obj < dist_to_light)  // 物体との距離が光源よりも近い場合
			{
				ray->marking_color = (t_vec3){0,1,1};
				return (true);
			}
		}
		i += 1;
	}
	ray->marking_color = (t_vec3){1,1,0};
	return (false);
}

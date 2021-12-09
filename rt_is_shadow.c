/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_is_shadow.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatsuka < rmatsuka@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 16:56:38 by rmatsuka          #+#    #+#             */
/*   Updated: 2021/12/09 17:00:24 by rmatsuka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#define EPS (double)(1.0/256.0)

bool	rt_is_shadow(
	const t_hit_record *actual,
	const t_scene *scene,
	t_hit_record *recs,
	const t_vec3 *light_pos)
{
	t_ray	shadow_ray;
	const t_vec3 v = mr_vec3_sub(*light_pos, actual->p); // 交点から光源へのベクトル
	const t_vec3 incident = mr_unit_vector(&v); // 入射ベクトル
	shadow_ray.origin = mr_vec3_add(actual->p, mr_vec3_mul_double(&incident, EPS)); // 入射方向に少しずらす
	shadow_ray.direction = incident;
	size_t i = 0;

	// 光源までの距離
	double dist_to_light = mr_vec3_length(&v) - EPS;

	while (i < scene->n_objects)
	{
		if (rt_hit_object(scene->objects[i], &shadow_ray, &recs[i]))
		{
			t_vec3 normal = shadow_ray.direction;
			t_vec3 tmp = mr_vec3_mul_double(&normal, recs[i].t); // シャドウレイからt倍する
			double dist_to_obj = mr_vec3_length(&tmp);
			if (dist_to_obj < dist_to_light)  // 物体との距離が光源よりも近い場合
			{
				return (true);
			}
		}
		i += 1;
	}
	return (false);
}

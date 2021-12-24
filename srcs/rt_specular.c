/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_specular.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 22:54:35 by rmatsuka          #+#    #+#             */
/*   Updated: 2021/12/24 03:48:29 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define COEF 0.3f
#define INTENSITY 1.0f
#define GLOSS 30.0f

t_vec3	rt_specular(
	const t_hit_record *rec,
	const t_vec3 *light,
	const t_vec3 *light_color,
	const t_ray *ray)
{
	const t_vec3	temp = mr_vec3_mul_double(&ray->direction, -1);
	const t_vec3	ray_inverse = mr_unit_vector(&temp); // レイの方向の逆向きの方向ベクトル(正規化済み)
	const t_vec3	temp2 = mr_vec3_sub(*light, rec->p);
	const t_vec3	light_out = mr_unit_vector(&temp2); // 反射面から光源を見る方向ベクトル
	const t_vec3	reflect_of_light = mr_vec3_sub( // light_out に対応する反射光のベクトル
						mr_vec3_mul_double(
							&rec->normal, mr_vec3_dot(rec->normal, light_out) * 2
						),
						light_out
					);

	if (!rec->hit)
	{
		return ((t_vec3){0, 0, 0});
	}
	// 反射が起きる条件:
	// - 光源とカメラが反射面を挟んで同じ側にある: これは拡散反射と同じ
	// - 
	const double rr = mr_vec3_dot(ray_inverse, reflect_of_light);
	if (rr < 0)
	{
		return ((t_vec3){0, 0, 0});
	}
	return (mr_vec3_mul_double(
			light_color,
			(COEF * INTENSITY * \
			pow(mr_vec3_dot(ray_inverse, reflect_of_light), GLOSS))));
}

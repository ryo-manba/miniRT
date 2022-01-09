/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_specular.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 22:54:35 by rmatsuka          #+#    #+#             */
/*   Updated: 2022/01/09 22:32:34 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define COEF 0.3
#define INTENSITY 100.0
#define GLOSS 30.0

// ray_inverse = レイの方向の逆向きの方向ベクトル(正規化済み)
// light_out = 反射面から光源を見る方向ベクトル
// reflect_of_light = light_out に対応する反射光のベクトル
t_vec3	rt_specular(
	const t_hit_record *rec,
	const t_vec3 *light,
	const t_vec3 *light_color,
	const t_ray *ray)
{
	const t_vec3	temp2 = mr_vec3_sub(*light, rec->p);
	const t_vec3	surface_to_light = mr_unit_vector(&temp2);
	const t_vec3	surface_to_reflection = mr_vec3_sub(
						surface_to_light,
						mr_vec3_mul_double(
						&rec->normal,
						mr_vec3_dot(rec->normal, surface_to_light) * 2
						)
					);
	const double	rr = mr_vec3_dot(
				mr_unit_vector(&ray->direction), surface_to_reflection);
	t_vec3			color;

	if (rr < 0)
	{
		return ((t_vec3){0, 0, 0});
	}
	color = mr_vec3_product(*light_color, rec->color);
	return (mr_vec3_mul_double(
			&color,
			(COEF * INTENSITY
				* pow(rr, GLOSS) / mr_vec3_length_squared(&temp2))));
}

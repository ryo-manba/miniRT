/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_diffuse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 22:03:25 by rmatsuka          #+#    #+#             */
/*   Updated: 2021/12/25 23:42:37 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define RATIO 1.0

// 光源とカメラが反射面を挟んで逆側にいる時反射は起きない
static double	pre_calc(
	const t_hit_record *rec,
	const t_element *light,
	const t_ray *ray)
{
	const t_vec3	light_in = mr_vec3_sub(rec->p, light->position);
	const double	cos_light = mr_vec3_dot(
						mr_unit_vector(&light_in), rec->normal);
	const double	cos_ray = mr_vec3_dot(
						mr_unit_vector(&ray->direction), rec->normal);
	const t_vec3	temp = mr_vec3_sub(rec->p, light->position);
	const double	r_light = mr_vec3_length_squared(&temp);

	if (cos_light * cos_ray <= 0)
		return (0);
	if (light->etype == RD_ET_SPOTLIGHT)
		return (fabs(cos_light * RATIO));
	return (fabs(cos_light * RATIO / r_light));
}

t_vec3	rt_diffuse(
	const t_hit_record *rec,
	const t_element *light,
	const t_vec3 *light_color,
	const t_ray *ray)
{
	const double	x = pre_calc(rec, light, ray);

	if (!rec->hit || x == 0)
		return ((t_vec3){0, 0, 0});
	return (mr_vec3_mul_double(light_color, x));
}

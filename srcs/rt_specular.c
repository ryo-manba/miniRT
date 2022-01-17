/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_specular.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 22:54:35 by rmatsuka          #+#    #+#             */
/*   Updated: 2022/01/17 12:39:01 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define INTENSITY 30.0
#define GLOSS 30.0

// color component by specular reflection.
t_vec3	rt_color_specular(
	const t_hit_record *rec,
	const t_element *light,
	const t_vec3 *light_color,
	const t_ray *ray)
{
	const t_vec3	temp2 = rt_get_incident_vector(rec, light, true);
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
			(INTENSITY
				* rec->element.k_specular
				* pow(rr, rec->element.gloss)
				/ mr_vec3_length_squared(&temp2))));
}

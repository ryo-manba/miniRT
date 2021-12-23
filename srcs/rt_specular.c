/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_specular.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatsuka < rmatsuka@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 22:54:35 by rmatsuka          #+#    #+#             */
/*   Updated: 2021/12/22 23:26:51 by rmatsuka         ###   ########.fr       */
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
	const t_vec3	ray_inverse = mr_unit_vector(&temp);
	const t_vec3	temp2 = mr_vec3_sub(*light, rec->p);
	const t_vec3	light_in = mr_unit_vector(&temp2);
	const t_vec3	reflect_of_light = mr_vec3_sub(
				mr_vec3_mul_double(
					&rec->normal, mr_vec3_dot(rec->normal, light_in) * 2),
					light_in);

	if (!rec->hit)
	{
		return ((t_vec3){0, 0, 0});
	}
	if (mr_vec3_dot(rec->normal, light_in) < 0 || \
		mr_vec3_dot(ray_inverse, reflect_of_light) < 0)
	{
		return ((t_vec3){0, 0, 0});
	}
	return (mr_vec3_mul_double(
			light_color,
			(COEF * INTENSITY * \
			pow(mr_vec3_dot(ray_inverse, reflect_of_light), GLOSS))));
}

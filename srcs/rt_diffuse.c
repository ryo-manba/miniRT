/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_diffuse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 22:03:25 by rmatsuka          #+#    #+#             */
/*   Updated: 2022/01/12 02:31:51 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static double	intensity(
	const t_hit_record *rec,
	const t_element *light)
{
	const t_vec3	light_in = mr_vec3_sub(rec->p, light->position);
	const double	cos_light = mr_vec3_dot(
						mr_unit_vector(&light_in), rec->normal);

	return (fabs(cos_light / \
			(LIGHT_DISTANCE_DECAY
				* mr_vec3_length_squared(&light_in))));
}

// color component by light diffusion.
t_vec3	rt_color_diffuse(
	const t_hit_record *rec,
	const t_element *light,
	const t_vec3 *light_color)
{
	double	x;
	t_vec3	color;

	color = *light_color;
	x = intensity(rec, light) * rec->element.k_diffuse;
	color = mr_vec3_product(*light_color, rec->color);
	return (mr_vec3_mul_double(&color, x));
}

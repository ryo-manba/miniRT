/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_diffuse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatsuka < rmatsuka@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 22:03:25 by rmatsuka          #+#    #+#             */
/*   Updated: 2022/01/05 00:24:15 by rmatsuka         ###   ########.fr       */
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
			pow(LIGHT_DISTANCE_DECAY * mr_vec3_length_squared(&light_in), 1)));
}

t_vec3	rt_diffuse(
	const t_hit_record *rec,
	const t_element *light,
	const t_vec3 *light_color)
{
	double	x;
	t_vec3	color;

	color = *light_color;
	x = intensity(rec, light);
	color = mr_vec3_product(*light_color, rec->color);
	return (mr_vec3_mul_double(&color, x));
}

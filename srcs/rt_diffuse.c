/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_diffuse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 22:03:25 by rmatsuka          #+#    #+#             */
/*   Updated: 2021/12/26 13:33:07 by corvvs           ###   ########.fr       */
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
	return (fabs(cos_light / pow(LIGHT_DISTANCE_DECAY * mr_vec3_length_squared(&light_in), 1)));
}

t_vec3	rt_diffuse(
	const t_hit_record *rec,
	const t_element *light,
	const t_vec3 *light_color)
{
	double	x;
	
	x = intensity(rec, light);
	return (mr_vec3_mul_double(light_color, x));
}

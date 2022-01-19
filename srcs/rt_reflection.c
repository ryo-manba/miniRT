/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_reflection.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 11:10:43 by corvvs            #+#    #+#             */
/*   Updated: 2022/01/17 19:55:05 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	set_light_color(t_vec3 *light_color,
	const t_hit_record *actual, t_element *light)
{
	t_vec3	q;
	double	w;
	double	ru;
	double	rv;

	if (light->etype != RD_ET_PYRAMIDLIGHT)
	{
		*light_color = light->color;
		return ;
	}
	q = mr_vec3_sub(actual->p, light->position);
	w = 2 * mr_vec3_dot(q, light->direction);
	ru = (mr_vec3_dot(q, light->direction_u) / (w * tan(light->fov)) + 0.5);
	rv = (mr_vec3_dot(q, light->direction_v) / (w * tan(light->fov2)) + 0.5);
	*light_color = rt_color_image(ru, rv, light);
}

static t_vec3	light_proc(
	t_ray *r,
	t_subscene *subscene,
	const t_hit_record *actual,
	t_element *light
)
{
	t_vec3	base_color;
	t_vec3	light_color;
	t_vec3	light_incident;

	mr_vec3_init(&base_color, 0, 0, 0);
	if (actual->hit && !rt_is_shadowed_from(actual, light, subscene, r))
	{
		set_light_color(&light_color, actual, light);
		light_incident = rt_get_incident_vector(actual, light);
		mr_vec3_add_comp(&base_color,
			rt_color_diffuse(actual, &light_incident, &light_color));
		mr_vec3_add_comp(&base_color,
			rt_color_specular(actual, &light_incident, &light_color, r));
	}
	return (base_color);
}

t_vec3	rt_reflect_ray(
	t_ray *r,
	t_subscene *subscene,
	t_hit_record *actual
)
{
	size_t			i;
	t_vec3			base_color;
	t_hit_record	actual_0;

	rt_set_tangent_space(actual);
	actual_0 = *actual;
	base_color = rt_color_ambient(subscene->info->scene->ambient->ratio,
			&subscene->info->scene->ambient->color, &actual_0.color);
	i = 0;
	while (i < subscene->info->scene->n_spotlights)
	{
		mr_vec3_add_comp(&base_color,
			light_proc(r, subscene, &actual_0,
				subscene->info->scene->spotlights[i]));
		i += 1;
	}
	i = 0;
	while (i < subscene->info->scene->n_lights)
	{
		mr_vec3_add_comp(&base_color,
			light_proc(r, subscene, &actual_0,
				subscene->info->scene->lights[i]));
		i += 1;
	}
	return (base_color);
}

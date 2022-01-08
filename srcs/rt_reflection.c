/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_reflection.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 11:10:43 by corvvs            #+#    #+#             */
/*   Updated: 2022/01/08 11:12:31 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_vec3	light_proc(
	t_ray *r,
	t_scene *scene,
	const t_hit_record *actual,
	t_element *light
)
{
	t_vec3	base_color;

	mr_vec3_init(&base_color, 0, 0, 0);
	if (actual->hit && !rt_is_shadow(actual, light, scene, r))
	{
		base_color = mr_vec3_add(base_color,
				rt_diffuse(actual, light, &light->color));
		base_color = mr_vec3_add(base_color,
				rt_specular(actual, &light->position, &light->color, r));
	}
	// else
	// 	return r->marking_color;
	return (base_color);
}

t_vec3	rt_reflect_ray(
	t_ray *r,
	t_scene *scene,
	const t_hit_record *actual
)
{
	size_t	i;
	t_vec3	base_color;

	base_color = rt_ambient(scene->ambient->ratio,
			&scene->ambient->color, &actual->color);
	i = 0;
	while (i < scene->n_spotlights)
	{
		base_color = mr_vec3_add(base_color,
				light_proc(r, scene, actual, scene->spotlights[i]));
		i += 1;
	}
	i = 0;
	while (i < scene->n_lights)
	{
		base_color = mr_vec3_add(base_color,
				light_proc(r, scene, actual, scene->lights[i]));
		i += 1;
	}
	return (base_color);
}

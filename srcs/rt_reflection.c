/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_reflection.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 11:10:43 by corvvs            #+#    #+#             */
/*   Updated: 2022/01/08 16:47:44 by corvvs           ###   ########.fr       */
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
		mr_vec3_add_comp(&base_color,
			rt_diffuse(actual, light, &light->color));
		mr_vec3_add_comp(&base_color,
			rt_specular(actual, &light->position, &light->color, r));
	}
	return (base_color);
}

t_vec3	rt_reflect_ray(
	t_ray *r,
	t_scene *scene,
	t_hit_record *actual
)
{
	size_t			i;
	t_vec3			base_color;
	t_hit_record	actual_0;

	rt_set_tangent_space(actual);
	actual_0 = *actual;
	base_color = rt_ambient(scene->ambient->ratio,
			&scene->ambient->color, &actual_0.color);
	i = 0;
	while (i < scene->n_spotlights)
	{
		mr_vec3_add_comp(&base_color,
			light_proc(r, scene, &actual_0, scene->spotlights[i]));
		i += 1;
	}
	i = 0;
	while (i < scene->n_lights)
	{
		mr_vec3_add_comp(&base_color,
			light_proc(r, scene, &actual_0, scene->lights[i]));
		i += 1;
	}
	return (base_color);
}

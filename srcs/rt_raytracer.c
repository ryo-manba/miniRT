/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_raytracer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 10:16:29 by corvvs            #+#    #+#             */
/*   Updated: 2022/01/08 11:12:13 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_vec3	sky_blue(const t_vec3 direction)
{
	const t_vec3	c2 = {1.0, 1.0, 1.0};
	const t_vec3	c1 = {0.5, 0.7, 1.0};
	const t_vec3	unit_direction = mr_unit_vector(&direction);
	const double	t = 0.5 * (unit_direction.y + 1.0);

	return (mr_vec3_add(
			mr_vec3_mul_double(&c1, t),
			mr_vec3_mul_double(&c2, 1 - t)));
}

static t_vec3	derive_color_for_ray(t_ray *r, t_scene *scene)
{
	t_hit_record	*actual;
	t_hit_record	actual_0;
	t_vec3			base_color;

	actual = rt_find_actual_hit(r, scene);
	if (!actual)
	{
		return (sky_blue(r->direction));
	}
	rt_set_tangent_space(actual);
	actual_0 = *actual;
	base_color = rt_reflect_ray(r, scene, &actual_0);
	base_color.x = fmin(base_color.x, 1);
	base_color.y = fmin(base_color.y, 1);
	base_color.z = fmin(base_color.z, 1);
	return (base_color);
}

static void	set_ray_for_pixel(t_scene *scene, t_ray *ray, int x, int y)
{
	const t_element	*cam = scene->camera;
	const t_vec3	ray_cross_screen = mr_vec3_add(
		mr_vec3_add(
			mr_vec3_mul_double(&scene->optics.screen_vertical,
				(scene->pixel_height - y) / scene->pixel_height),
			mr_vec3_mul_double(&scene->optics.screen_horizontal,
				x / scene->pixel_width)
		),
		scene->optics.screen_bottomleft
	);

	if (cam->fov == 0)
	{
		ray->origin = mr_vec3_sub(ray_cross_screen, cam->direction);
		ray->direction = cam->direction;
	}
	else
	{
		ray->origin = cam->position;
		ray->direction = mr_vec3_sub(ray_cross_screen, ray->origin);
	}
}

static void	setup_optics(t_scene *scene)
{
	t_optics		*opt;
	const t_element	*cam = scene->camera;

	opt = &scene->optics;
	opt->screen_width = 2.0;
	opt->screen_height = opt->screen_width / scene->aspect_ratio;
	if (scene->camera->fov == 0)
		opt->focal_length = 1;
	else
		opt->focal_length = opt->screen_width / (2 * tan(cam->fov));
	opt->screen_horizontal.x = opt->screen_width;
	opt->screen_vertical.y = opt->screen_height;
	opt->screen_horizontal
		= rt_orient_vector(&opt->screen_horizontal, &cam->direction);
	opt->screen_vertical
		= rt_orient_vector(&opt->screen_vertical, &cam->direction);
	opt->screen_center = mr_vec3_add(cam->position,
			mr_vec3_mul_double(&cam->direction, opt->focal_length));
	opt->screen_bottomleft = mr_vec3_sub(
			mr_vec3_sub(
				opt->screen_center,
				mr_vec3_mul_double(&opt->screen_horizontal, 0.5)
				), mr_vec3_mul_double(&opt->screen_vertical, 0.5));
}

void	rt_raytrace(t_info *info, t_scene *scene)
{
	int		i;
	int		j;
	t_ray	ray;

	setup_optics(scene);
	ray.for_shadow = false;
	j = 0;
	while (j < scene->pixel_height)
	{
		i = 0;
		while (i < scene->pixel_width)
		{
			set_ray_for_pixel(scene, &ray, i, j);
			mr_mlx_pixel_put(
				&info->img, i, j, derive_color_for_ray(&ray, scene));
			i += 1;
		}
		j += 1;
	}
}

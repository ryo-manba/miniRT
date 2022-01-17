/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 19:00:14 by corvvs            #+#    #+#             */
/*   Updated: 2022/01/17 20:30:17 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "rt_scene.h"
#include "mr_vec3.h"
#include "mr_utils.h"
#include "mr_camera.h"

static const double	g_aspect_ratio = 16.0 / 9.0;
static const int	g_height = 1080;

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

static bool	setup_mlx(t_info *info)
{
	const double	width = g_aspect_ratio * g_height;

	info->mlx = mlx_init();
	if (!info->mlx)
		mr_bailout(info, "bad mlx(mlx)");
	info->win = mlx_new_window(info->mlx, width, g_height, "miniRT");
	if (!info->win)
		mr_bailout(info, "bad mlx(window)");
	info->img.img = mlx_new_image(info->mlx, width, g_height);
	if (!info->img.img)
		mr_bailout(info, "bad mlx(image)");
	info->img.addr = mlx_get_data_addr(
			info->img.img,
			&info->img.bpp,
			&info->img.line_len,
			&info->img.endian);
	if (!info->img.addr)
		mr_bailout(info, "bad mlx(image data addr)");
	return (true);
}

void	setup(int argc, char **argv, t_info *info)
{
	int	i;

	if (argc != 2)
		mr_bailout(info, "will be accepted just one argument as rt-file path");
	if (rd_read_scene(argv[1], info->scene) == false)
		exit(1);
	setup_mlx(info);
	info->scene->threads = THREADS;
	info->scene->recss = (t_hit_record **)ft_calloc(info->scene->threads,
			sizeof(t_hit_record *));
	if (!info->scene->recss)
		mr_bailout(info, "bad alloc(recs)");
	i = -1;
	while (++i < info->scene->threads)
	{
		info->scene->recss[i] = (t_hit_record *)malloc(
				(info->scene->n_objects + 1) * sizeof(t_hit_record));
		if (!info->scene->recss[i])
			mr_bailout(info, "bad alloc(recs)");
	}
	info->scene->aspect_ratio = g_aspect_ratio;
	info->scene->pixel_height = g_height;
	info->scene->pixel_width = g_aspect_ratio * g_height;
	mr_read_image_files(info);
	setup_optics(info->scene);
}

int	main(int argc, char **argv)
{
	t_info		info;
	t_scene		scene;

	ft_bzero(&info, sizeof(t_info));
	ft_bzero(&scene, sizeof(t_scene));
	info.scene = &scene;
	setup(argc, argv, &info);
	rt_raytrace(&info, &scene);
	mlx_put_image_to_window(info.mlx, info.win, info.img.img, 0, 0);
	mlx_hook(info.win,
		EVENT_CLOSE, MASK_CLOSE, &mr_exit_window, &info);
	mlx_hook(info.win,
		EVENT_KEY_PRESS, MASK_KEY_PRESS, &mr_hook_key_press, &info);
	mlx_hook(info.win, EVENT_EXPOSE, MASK_EXPOSE, &mr_expose_window, &info);
	mlx_loop(info.mlx);
	return (0);
}

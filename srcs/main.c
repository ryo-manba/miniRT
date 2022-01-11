/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 19:00:14 by corvvs            #+#    #+#             */
/*   Updated: 2022/01/11 11:32:07 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "rt_scene.h"
#include "mr_vec3.h"
#include "mr_utils.h"
#include "mr_camera.h"

static const double	g_aspect_ratio = 16.0 / 9.0;
static const int	g_height = 320;

static bool	setup_info(t_info *info)
{
	const double	width = g_aspect_ratio * g_height;

	info->mlx = mlx_init();
	if (!info->mlx)
		return (false);
	info->win = mlx_new_window(info->mlx, width, g_height, "miniRT");
	if (!info->win)
		return (false);
	info->img.img = mlx_new_image(info->mlx, width, g_height);
	if (!info->img.img)
		return (false);
	info->img.addr = mlx_get_data_addr(
			info->img.img,
			&info->img.bpp,
			&info->img.line_len,
			&info->img.endian);
	return (true);
}

int	main(int argc, char **argv)
{
	t_info	info;
	t_scene	scene;

	if (argc != 2)
	{
		printf("Error: Invalid Argument\n");
		return (1);
	}
	if (rd_read_scene(argv[1], &scene) == false)
	{
		return (1);
	}
	if (setup_info(&info) == false)
	{
		return (1);
	}
	scene.recs = (t_hit_record *)malloc((scene.n_objects + 1) * sizeof(t_hit_record));
	scene.aspect_ratio = g_aspect_ratio;
	scene.pixel_height = g_height;
	scene.pixel_width = g_aspect_ratio * g_height;
	info.scene = &scene;
	mr_read_image_files(&info, &scene);
	rt_raytrace(&info, &scene);
	mlx_put_image_to_window(info.mlx, info.win, info.img.img, 0, 0);
	mlx_hook(info.win, 17, 1L << 17, &mr_exit_window, &info);
	mlx_loop(info.mlx);
	return (0);
}

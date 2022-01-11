/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mr_mlx_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 23:43:35 by rmatsuka          #+#    #+#             */
/*   Updated: 2022/01/11 01:59:51 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	vec3_to_color(const t_vec3 *v3)
{
	return (rt_create_trgb(0,
			(int)(v3->x * 255), (int)(v3->y * 255), (int)(v3->z * 255)));
}

void	mr_mlx_pixel_put(t_img *img, int x, int y, const t_vec3 v3)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = vec3_to_color(&v3);
}

unsigned int	mr_mlx_pixel_get(t_img *img, int x, int y)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	return (*(unsigned int *)dst);
}

int	mr_exit_window(t_info *info)
{
	mr_destroy_image_files(info, info->scene);
	rd_destroy_scene(info->scene);
	mlx_destroy_window(info->mlx, info->win);
	exit(0);
}

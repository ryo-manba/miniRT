/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mr_mlx_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 23:43:35 by rmatsuka          #+#    #+#             */
/*   Updated: 2022/01/12 02:46:32 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define SHIFT_T 24
#define SHIFT_R 16
#define SHIFT_G 8
#define SHIFT_B 0

static int	vec3_to_color(const t_vec3 *v3)
{
	return ((0 << SHIFT_T)
		| ((int)(v3->x * 255) << SHIFT_R)
			| ((int)(v3->y * 255) << SHIFT_G)
			| ((int)(v3->z * 255) << SHIFT_B));
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
	mr_destroy_image_files(info);
	rd_destroy_scene(info->scene);
	mlx_destroy_window(info->mlx, info->win);
	mlx_destroy_display(info->mlx);
	ft_malloc_balance();
	exit(0);
	return (0);
}

int	mr_hook_key_press(int key, t_info *info)
{
	if (key == KEY_ESC)
		mr_exit_window(info);
	return (0);
}

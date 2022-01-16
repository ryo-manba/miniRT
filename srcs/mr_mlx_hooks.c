/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mr_mlx_hooks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatsuka < rmatsuka@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 17:45:59 by rmatsuka          #+#    #+#             */
/*   Updated: 2022/01/14 17:53:40 by rmatsuka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	mr_expose_window(t_info *info)
{
	mlx_put_image_to_window(info->mlx, info->win, info->img.img, 0, 0);
	return (0);
}

int	mr_hook_key_press(int key, t_info *info)
{
	if (key == KEY_ESC)
		mr_exit_window(info);
	return (0);
}

int	mr_exit_window(t_info *info)
{
	mr_destroy_image_files(info);
	rd_destroy_scene(info->scene);
	if (info->mlx && info->img.img)
		mlx_destroy_image(info->mlx, info->img.img);
	if (info->mlx && info->win)
		mlx_destroy_window(info->mlx, info->win);
	if (info->mlx)
		mlx_destroy_display(info->mlx);
	free(info->mlx);
	exit(0);
	return (0);
}

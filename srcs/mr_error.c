/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mr_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatsuka < rmatsuka@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 18:04:00 by corvvs            #+#    #+#             */
/*   Updated: 2022/01/12 16:01:53 by rmatsuka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// print error message and exit miniRT cleanly.
void	mr_bailout(t_info *info, const char *error)
{
	printf("\e[93mError\n%s\e[m\n", error);
	if (info)
	{
		mr_destroy_image_files(info);
		if (info->scene)
			rd_destroy_scene(info->scene);
		if (info->mlx && info->win)
			mlx_destroy_window(info->mlx, info->win);
		if (info->mlx)
			mlx_destroy_display(info->mlx);
	}
	exit(1);
}

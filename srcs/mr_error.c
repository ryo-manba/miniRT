/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mr_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 18:04:00 by corvvs            #+#    #+#             */
/*   Updated: 2022/01/11 19:05:31 by corvvs           ###   ########.fr       */
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
	ft_malloc_balance();
	exit(1);
}

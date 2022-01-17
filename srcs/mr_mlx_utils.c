/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mr_mlx_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatsuka < rmatsuka@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 23:43:35 by rmatsuka          #+#    #+#             */
/*   Updated: 2022/01/14 17:47:18 by rmatsuka         ###   ########.fr       */
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

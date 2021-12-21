/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_texture_sphere.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatsuka < rmatsuka@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 13:39:11 by rmatsuka          #+#    #+#             */
/*   Updated: 2021/12/21 16:48:18 by rmatsuka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	rt_texture_sphere(t_hit_record *rec)
{
	const double theta = atan2(rec->normal.x, rec->normal.z);
	const double phi = acos(rec->normal.y);

	rec->tex.u = 1 - ((theta / (M_PI)));
	rec->tex.v = 1 - ((phi / M_PI));
}

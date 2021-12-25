/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_texture_cylinder.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 13:41:07 by rmatsuka          #+#    #+#             */
/*   Updated: 2021/12/25 19:08:18 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static double	calc_theta(
	const t_hit_record *rec,
	const t_element *el,
	const t_vec3 *ndx)
{
	const t_vec3	dz = rt_coord_turn_around_90(ndx, &el->direction);
	const double	x = mr_vec3_dot(mr_vec3_sub(rec->p, el->position), *ndx);
	const double	z = mr_vec3_dot(mr_vec3_sub(rec->p, el->position), dz);

	return (atan2(x, z));
}

static double	calc_phi(const t_hit_record *rec, const t_element *el)
{
	const double	temp = mr_vec3_dot(
			mr_vec3_sub(rec->p, el->position), el->direction);

	return (temp * M_PI / el->height);
}

void	rt_texture_cylinder(t_hit_record *rec, const t_element *el)
{
	const t_vec3	ndx = rt_coord_perpendicular_unit(&el->direction);
	const double	phi = calc_phi(rec, el);
	const double	theta = calc_theta(rec, el, &ndx);

	rec->tex.u = theta / M_PI;
	rec->tex.v = phi / (2 * M_PI);
}

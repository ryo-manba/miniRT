/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_texture_cylinder.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatsuka < rmatsuka@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 13:41:07 by rmatsuka          #+#    #+#             */
/*   Updated: 2021/12/21 23:42:49 by rmatsuka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// If the viewpoint is on the central axis of the cylinder,
// shift the reference point.
static t_vec3	get_point(const t_vec3 *dir)
{
	if (dir->y != 0 || dir->z != 0)
		return ((t_vec3){1, 0, 0});
	if (dir->z != 0 || dir->x != 0)
		return ((t_vec3){0, 1, 0});
	if (dir->x != 0 || dir->y != 0)
		return ((t_vec3){0, 0, 1});
	else
	{
		return ((t_vec3){0, 0, 0});
	}
}

static double	calc_theta(
	const t_hit_record *rec,
	const t_element *el,
	const t_vec3 *ndx)
{
	const t_vec3	temp = mr_vec3_mul_double(
		&el->direction, mr_vec3_dot(el->direction, *ndx));
	const t_vec3	dz = mr_vec3_add(temp, mr_vec3_cross(&el->direction, ndx));
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
	const t_vec3	r = get_point(&el->direction);
	const t_vec3	dx = mr_vec3_cross(&el->direction, &r);
	const t_vec3	ndx = mr_unit_vector(&dx);
	const double	phi = calc_phi(rec, el);
	const double	theta = calc_theta(rec, el, &ndx);

	rec->tex.u = theta / M_PI;
	rec->tex.v = phi / (2 * M_PI);
}

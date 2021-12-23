/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_texture_plane.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatsuka < rmatsuka@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 13:30:58 by rmatsuka          #+#    #+#             */
/*   Updated: 2021/12/21 18:52:17 by rmatsuka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_vec3	calc_perpendicular(t_vec3 *normal)
{
	t_vec3	p;

	if (normal->x != 0)
	{
		p.y = 0;
		p.z = sqrt(1 / (1 + pow((normal->z / normal->x), 2)));
		p.x = -normal->z / normal->x * p.z;
	}
	else if (normal->z != 0.0)
	{
		p.y = 0;
		p.x = sqrt(1 / (1 + pow((normal->x / normal->z), 2)));
		p.z = -normal->x / normal->z * p.x;
	}
	else
	{
		p.z = 0;
		p.x = sqrt(1 / (1 + pow((normal->x / normal->y), 2)));
		p.y = -normal->x / normal->y * p.x;
	}
	return (p);
}

void	rt_texture_plane(t_hit_record *rec)
{
	const t_vec3	p1 = calc_perpendicular(&rec->normal);
	const t_vec3	p2 = mr_vec3_add(
				mr_vec3_mul_double(&rec->normal, mr_vec3_dot(rec->normal, p1)),
				mr_vec3_cross(&rec->normal, &p1));

	rec->tex.u = mr_vec3_dot(mr_vec3_sub(rec->p, rec->element.position), p1);
	rec->tex.v = mr_vec3_dot(mr_vec3_sub(rec->p, rec->element.position), p2);
}

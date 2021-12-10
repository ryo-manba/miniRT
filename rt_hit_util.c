/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_hit_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 20:29:15 by corvvs            #+#    #+#             */
/*   Updated: 2021/12/10 12:18:18 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	rt_hit_point(double t, const t_ray *ray)
{
	return (mr_vec3_add((ray->origin),
		(mr_vec3_mul_double(&ray->direction, t))));
}

void	rt_after_hit(
	const t_element *el,
	const t_ray *ray,
	t_hit_record *rec)
{
	if (rec->hit)
	{
		rec->element = *el;
		rec->cos = mr_vec3_dot(mr_unit_vector(&ray->direction), rec->normal);
		rec->color = el->color;
	}
	else
	{
		rec->t = rd_inf(true);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_texture_plane.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 13:30:58 by rmatsuka          #+#    #+#             */
/*   Updated: 2021/12/25 21:19:39 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	rt_texture_plane(t_hit_record *rec)
{
	const t_vec3	p1 = rt_coord_perpendicular_unit(&rec->normal);
	const t_vec3	p2 = rt_coord_turn_around_90(&p1, &rec->normal);

	rec->tex.u = mr_vec3_dot(mr_vec3_sub(rec->p, rec->element.position), p1);
	rec->tex.v = mr_vec3_dot(mr_vec3_sub(rec->p, rec->element.position), p2);
}

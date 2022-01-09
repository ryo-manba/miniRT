/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mr_vec3_operator_composit.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 19:40:12 by corvvs            #+#    #+#             */
/*   Updated: 2022/01/08 15:28:06 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mr_vec3.h"

void	mr_vec3_add_comp(t_vec3 *u, const t_vec3 v)
{
	u->x += v.x;
	u->y += v.y;
	u->z += v.z;
}

void	mr_vec3_sub_comp(t_vec3 *u, const t_vec3 v)
{
	u->x -= v.x;
	u->y -= v.y;
	u->z -= v.z;
}

void	mr_vec3_cross_comp(t_vec3 *u, const t_vec3 *v)
{
	double	a;
	double	b;

	a = u->x;
	b = u->y;
	u->x = b * v->z - u->z * v->y;
	u->y = u->z * v->x - a * v->z;
	u->z = a * v->y - b * v->x;
}

void	mr_vec3_mul_double_comp(t_vec3 *u, const double t)
{
	u->x *= t;
	u->y *= t;
	u->z *= t;
}

void	mr_normalize_comp(t_vec3 *v)
{
	mr_vec3_mul_double_comp(v, 1 / mr_vec3_length(v));
}

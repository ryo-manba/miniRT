/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mr_vec3_operator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 19:40:12 by corvvs            #+#    #+#             */
/*   Updated: 2021/12/08 19:40:44 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mr_vec3.h"

t_vec3	mr_vec3_add(const t_vec3 u, const t_vec3 v)
{
	t_vec3	add;

	add.x = u.x + v.x;
	add.y = u.y + v.y;
	add.z = u.z + v.z;
	return (add);
}

t_vec3	mr_vec3_sub(const t_vec3 u, const t_vec3 v)
{
	t_vec3	sub;

	sub.x = u.x - v.x;
	sub.y = u.y - v.y;
	sub.z = u.z - v.z;
	return (sub);
}

double	mr_vec3_dot(const t_vec3 u, const t_vec3 v)
{
	return ((u.x * v.x) + (u.y * v.y) + (u.z * v.z));
}

t_vec3	mr_vec3_cross(const t_vec3 *u, const t_vec3 *v)
{
	t_vec3	cross;

	cross.x = u->y * v->z - u->z * v->y;
	cross.y = u->z * v->x - u->x * v->z;
	cross.z = u->x * v->y - u->y * v->x;
	return (cross);
}

void	mr_vec3_init(t_vec3 *vec3, double x, double y, double z)
{
	vec3->x = x;
	vec3->y = y;
	vec3->z = z;
}

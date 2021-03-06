/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mr_vec3_operator2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 19:40:12 by corvvs            #+#    #+#             */
/*   Updated: 2022/01/08 13:40:35 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mr_vec3.h"

t_vec3	mr_vec3_product(const t_vec3 u, const t_vec3 v)
{
	t_vec3	prod;

	prod.x = u.x * v.x;
	prod.y = u.y * v.y;
	prod.z = u.z * v.z;
	return (prod);
}

void	mr_normalize_color(t_vec3 *p)
{
	p->x /= 255.0;
	p->y /= 255.0;
	p->z /= 255.0;
}

t_vec3	mr_vec_cutoff(t_vec3 p)
{
	p.x = fmin(p.x, 1);
	p.y = fmin(p.y, 1);
	p.z = fmin(p.z, 1);
	return (p);
}

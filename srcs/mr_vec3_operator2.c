/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mr_vec3_operator2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 19:40:12 by corvvs            #+#    #+#             */
/*   Updated: 2022/01/02 18:15:33 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mr_vec3.h"

t_vec3	mr_vec3_product(t_vec3 u, t_vec3 v)
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

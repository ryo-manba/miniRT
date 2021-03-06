/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 20:43:46 by corvvs            #+#    #+#             */
/*   Updated: 2022/01/08 11:18:08 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	vec3_debug(const t_vec3 *vec)
{
	printf("(x,y,z) = (%f, %f, %f)\n", vec->x, vec->y, vec->z);
}

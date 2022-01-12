/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_fmath.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 03:52:38 by corvvs            #+#    #+#             */
/*   Updated: 2022/01/12 04:19:37 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	rt_fmod(double x, double y)
{
	if (x >= 0)
		return (fmod(x, y));
	else
		return (y - fmod(-x, y));
}

double	rt_floor(double x)
{
	if (x >= 0)
		return (floor(x));
	else
		return (-ceil(-x));
}

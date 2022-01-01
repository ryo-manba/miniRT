/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_coord.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 18:03:21 by corvvs            #+#    #+#             */
/*   Updated: 2021/12/31 18:47:01 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_COORD_H
# define RT_COORD_H

# include "mr_common.h"
# define Y0 ((t_vec3){0, 1, 0})
# define Z0 ((t_vec3){0, 0, 1})

typedef struct s_equation2
{
	double	a;
	double	b_half;
	double	c;
	int		solutions;
	double	t1;
	double	t2;
}	t_equation2;

int		rt_solve_equation2(t_equation2 *arg);

t_vec3	rt_coord_perpendicular_unit(const t_vec3 *u);
t_vec3	rt_coord_turn_around_90(const t_vec3 *u, const t_vec3 *n);

#endif

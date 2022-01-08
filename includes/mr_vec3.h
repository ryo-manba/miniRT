/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mr_vec3.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 19:36:17 by corvvs            #+#    #+#             */
/*   Updated: 2022/01/08 15:29:08 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MR_VEC3_H
# define MR_VEC3_H
# include "mr_common.h"
# include <math.h>

/* mr_vec3_operator */
t_vec3	mr_vec3_add(const t_vec3 u, const t_vec3 v);
t_vec3	mr_vec3_sub(const t_vec3 u, const t_vec3 v);
double	mr_vec3_dot(const t_vec3 u, const t_vec3 v);
t_vec3	mr_vec3_cross(const t_vec3 *u, const t_vec3 *v);
void	mr_vec3_init(t_vec3 *vec3, double x, double y, double z);

/* mr_vec3_utils */
t_vec3	mr_vec3_mul_double(const t_vec3 *u, const double t);
t_vec3	mr_vec3_div_double(const t_vec3 *v, const double t);
t_vec3	mr_unit_vector(const t_vec3 *v);
double	mr_vec3_length(const t_vec3 *v);
double	mr_vec3_length_squared(const t_vec3 *v);

t_vec3	mr_vec3_product(const t_vec3 u, const t_vec3 v);
void	mr_normalize_color(t_vec3 *p);
t_vec3	mr_vec_cutoff(t_vec3 p);

void	mr_vec3_add_comp(t_vec3 *u, const t_vec3 v);
void	mr_vec3_sub_comp(t_vec3 *u, const t_vec3 v);
void	mr_vec3_cross_comp(t_vec3 *u, const t_vec3 *v);
void	mr_vec3_mul_double_comp(t_vec3 *u, const double t);
void	mr_normalize_comp(t_vec3 *v);

#endif

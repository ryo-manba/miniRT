/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_coord.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 18:03:21 by corvvs            #+#    #+#             */
/*   Updated: 2021/12/24 18:07:14 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_COORD_H
# define RT_COORD_H

# include "mr_common.h"

t_vec3	rt_coord_perpendicular_unit(const t_vec3 *u);
t_vec3	rt_coord_turn_around_90(const t_vec3 *u, const t_vec3 *n);

#endif

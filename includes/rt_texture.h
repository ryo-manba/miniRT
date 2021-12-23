/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_texture.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatsuka < rmatsuka@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 13:34:21 by rmatsuka          #+#    #+#             */
/*   Updated: 2021/12/21 16:21:59 by rmatsuka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_TEXTURE_H
# define RT_TEXTURE_H

# include "rt_scene.h"

void	rt_texture_plane(t_hit_record *rec);
void	rt_texture_sphere(t_hit_record *rec);
void	rt_texture_cylinder(t_hit_record *rec, const t_element *el);

#endif

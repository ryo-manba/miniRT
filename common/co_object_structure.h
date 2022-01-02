/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   co_object_structure.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 20:02:10 by corvvs            #+#    #+#             */
/*   Updated: 2022/01/02 18:08:28 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CO_OBJECT_STRUCTURE_H
# define CO_OBJECT_STRUCTURE_H

# include "co_geometric_structure.h"
# include "co_image_structure.h"
# include <stdlib.h>

typedef enum e_element_type
{
	RD_ET_DUMMY,
	RD_ET_AMBIENT,
	RD_ET_CAMERA,
	RD_ET_LIGHT,
	RD_ET_SPHERE,
	RD_ET_PLANE,
	RD_ET_CYLINDER,
	RD_ET_CONE,
	RD_ET_SPOTLIGHT,
	RD_ET_UNEXPECTED,
}	t_element_type;

typedef enum e_texture_type
{
	RD_TT_DUMMY,
	RD_TT_TEXMAP,
	RD_TT_CHECKER,
	RD_TT_ELEMENT,
}	t_texture_type;

typedef struct s_element
{
	t_element_type		etype;
	t_vec3				position;
	t_vec3				direction;
	t_vec3				color;
	double				ratio;
	double				radius;
	double				diameter;
	double				height;
	double				fov;
	struct s_element	*next;
	size_t				id;
	t_texture_type		textype;
	t_img				*texture;
	t_img				*bumpmap;
}	t_element;

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   co_object_structure.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 20:02:10 by corvvs            #+#    #+#             */
/*   Updated: 2022/01/11 21:44:36 by corvvs           ###   ########.fr       */
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
	RD_ET_PARABOLOID,
	RD_ET_CONE,
	RD_ET_SPOTLIGHT,
	RD_ET_TEXTURE,
	RD_ET_CHECKER,
	RD_ET_BUMPMAP,
	RD_ET_MATERIAL,
	RD_ET_UNEXPECTED,
}	t_element_type;

typedef struct s_element
{
	t_element_type		etype;
	t_vec3				position;
	t_vec3				direction;
	t_vec3				color;
	t_vec3				focalpoint;
	double				ratio;
	double				radius;
	double				diameter;
	double				height;
	double				fov;
	struct s_element	*next;
	struct s_element	*tex_el;
	struct s_element	*bump_el;
	double				gloss;
	double				k_diffuse;
	double				k_specular;

	char				*xpm_file_path;
	double				freq_u;
	double				freq_v;
	t_vec3				subcolor;
	t_img				*image;
}	t_element;

#endif

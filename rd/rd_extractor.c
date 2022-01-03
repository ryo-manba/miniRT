/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_extractor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 11:35:51 by corvvs            #+#    #+#             */
/*   Updated: 2022/01/03 22:26:30 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rd_read.h"

static bool	extract_double_scalar(const char *str, void *slot)
{
	double	v;

	if (!str)
	{
		return (false);
	}
	v = rd_str_to_double(str);
	*(double *)slot = v;
	return (rd_is_finite(v));
}

static bool	extract_double_vector(const char *str, void *slot)
{
	t_vec3	*vecslot;

	if (!str)
	{
		return (false);
	}
	vecslot = (t_vec3 *)slot;
	rd_vectorize(str, vecslot);
	return (rd_is_finite(vecslot->x));
}

static bool	extract_string(const char *str, void *slot)
{
	char	*dupped;

	if (!str)
	{
		return (false);
	}
	dupped = ft_strdup(str);
	if (!dupped)
	{
		return (false);
	}
	*(char **)slot = dupped;
	return (ft_strlen(str) > 0);
}

static const t_element_info_extractor	g_ambient_extractors[] = {
	extract_double_scalar, // ratio
	extract_double_vector, // color
	NULL,
};

static const t_element_info_extractor	g_camera_extractors[] = {
	extract_double_vector, // position
	extract_double_vector, // direction
	extract_double_scalar, // fov
	NULL,
};

static const t_element_info_extractor	g_light_extractors[] = {
	extract_double_vector, // position
	extract_double_scalar, // ratio
	extract_double_vector, // color
	NULL,
};

static const t_element_info_extractor	g_sphere_extractors[] = {
	extract_double_vector, // position
	extract_double_scalar, // diameter
	extract_double_vector, // color
	NULL,
};

static const t_element_info_extractor	g_plane_extractors[] = {
	extract_double_vector, // posiiton
	extract_double_vector, // direction
	extract_double_vector, // color
	NULL,
};

static const t_element_info_extractor	g_cylinder_extractors[] = {
	extract_double_vector, // posiiton
	extract_double_vector, // direction
	extract_double_scalar, // diameter
	extract_double_scalar, // height
	extract_double_vector, // color
	NULL,
};

static const t_element_info_extractor	g_cone_extractors[] = {
	extract_double_vector, // posiiton
	extract_double_vector, // direction
	extract_double_scalar, // fov
	extract_double_vector, // color
	NULL,
};

static const t_element_info_extractor	g_spotlight_extractors[] = {
	extract_double_vector, // posiiton
	extract_double_vector, // direction
	extract_double_scalar, // fov
	extract_double_scalar, // ratio
	extract_double_vector, // color
	NULL,
};

static const t_element_info_extractor	g_texture_extractors[] = {
	extract_string, // xpm_file_path
	extract_double_scalar, // freq_u
	extract_double_scalar, // freq_v
	NULL,
};

static const t_element_info_extractor	g_checker_extractors[] = {
	extract_double_scalar, // freq_u
	extract_double_scalar, // freq_v
	extract_double_vector, // color
	extract_double_vector, // subcolor
	NULL,
};

static const t_element_info_extractor	g_bumpmap_extractors[] = {
	extract_string, // xpm_file_path
	extract_double_scalar, // freq_u
	extract_double_scalar, // freq_v
	NULL,
};

static bool	extract_seq(
	const char **words,
	const t_element_info_extractor *extractors,
	void **addrs)
{
	size_t	i;

	i = 0;
	while (words[i + 1])
	{
		if (!(extractors[i])(words[i + 1], addrs[i]))
			return (false);
		i += 1;
	}
	return (true);
}

static const t_element_info_extractor	*g_list_of_extractors[] = {
	NULL,
	g_ambient_extractors,
	g_camera_extractors,
	g_light_extractors,
	g_sphere_extractors,
	g_plane_extractors,
	g_cylinder_extractors,
	g_cone_extractors,
	g_spotlight_extractors,
	g_texture_extractors,
	g_checker_extractors,
	g_bumpmap_extractors,
};

static void	**element_pointers(
	t_element *el
)
{
	if (el->etype == RD_ET_AMBIENT)
		return ((void *[]){&el->ratio, &el->color});
	if (el->etype == RD_ET_CAMERA)
		return ((void *[]){&el->position, &el->direction, &el->fov});
	if (el->etype == RD_ET_LIGHT)
		return ((void *[]){&el->position, &el->ratio, &el->color});
	if (el->etype == RD_ET_SPHERE)
		return ((void *[]){&el->position, &el->diameter, &el->color});
	if (el->etype == RD_ET_PLANE)
		return ((void *[]){&el->position, &el->direction, &el->color});
	if (el->etype == RD_ET_CYLINDER)
		return ((void *[]){&el->position, &el->direction,
			&el->diameter, &el->height, &el->color});
	if (el->etype == RD_ET_CONE)
		return ((void *[]){&el->position, &el->direction,
			&el->fov, &el->color});
	if (el->etype == RD_ET_SPOTLIGHT)
		return ((void *[]){&el->position, &el->direction,
			&el->fov, &el->ratio, &el->color});
	if (el->etype == RD_ET_TEXTURE || el->etype == RD_ET_BUMPMAP)
		return ((void *[]){&el->xpm_file_path, &el->freq_u, &el->freq_v});
	if (el->etype == RD_ET_CHECKER)
		return ((void *[]){&el->freq_u, &el->freq_v,
			&el->color, &el->subcolor});
	return (NULL);
}

t_element	*rd_extract_element(
	t_element_type etype,
	const char **words)
{
	t_element	*el;
	double		r;

	el = (t_element *)ft_calloc(1, sizeof(t_element));
	if (!el)
		return (NULL);
	el->etype = etype;
	if (!extract_seq(words, g_list_of_extractors[el->etype],
			element_pointers(el)))
	{
		free(el);
		return (NULL);
	}
	el->radius = el->diameter / 2;
	r = mr_vec3_length(&el->direction);
	if (r == 0)
		r = 1;
	el->direction = mr_vec3_mul_double(&el->direction, 1 / r);
	el->color = mr_vec3_mul_double(&el->color, 1 / 255.0);
	el->subcolor = mr_vec3_mul_double(&el->subcolor, 1 / 255.0);
	printf("el: %p(%p)\n", el, el->next);
	return (el);
}

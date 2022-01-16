/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_extractor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 11:35:51 by corvvs            #+#    #+#             */
/*   Updated: 2022/01/14 22:21:16 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rd_read.h"

static const t_element_info_extractor	g_ambient_extractors[] = {
	rd_extract_double_scalar, // ratio
	rd_extract_double_vector, // color
	NULL,
};

static const t_element_info_extractor	g_camera_extractors[] = {
	rd_extract_double_vector, // position
	rd_extract_double_vector, // direction
	rd_extract_double_scalar, // fov
	NULL,
};

static const t_element_info_extractor	g_light_extractors[] = {
	rd_extract_double_vector, // position
	rd_extract_double_scalar, // ratio
	rd_extract_double_vector, // color
	NULL,
};

static const t_element_info_extractor	g_sphere_extractors[] = {
	rd_extract_double_vector, // position
	rd_extract_double_scalar, // diameter
	rd_extract_double_vector, // color
	NULL,
};

static const t_element_info_extractor	g_plane_extractors[] = {
	rd_extract_double_vector, // posiiton
	rd_extract_double_vector, // direction
	rd_extract_double_vector, // color
	NULL,
};

static const t_element_info_extractor	g_cylinder_extractors[] = {
	rd_extract_double_vector, // posiiton
	rd_extract_double_vector, // direction
	rd_extract_double_scalar, // diameter
	rd_extract_double_scalar, // height
	rd_extract_double_vector, // color
	NULL,
};

static const t_element_info_extractor	g_paraboloid_extractors[] = {
	rd_extract_double_vector, // focalpoint
	rd_extract_double_vector, // posiiton
	rd_extract_double_vector, // direction
	rd_extract_double_vector, // color
	NULL,
};

static const t_element_info_extractor	g_cone_extractors[] = {
	rd_extract_double_vector, // posiiton
	rd_extract_double_vector, // direction
	rd_extract_double_scalar, // fov
	rd_extract_double_vector, // color
	NULL,
};

static const t_element_info_extractor	g_spotlight_extractors[] = {
	rd_extract_double_vector, // posiiton
	rd_extract_double_vector, // direction
	rd_extract_double_scalar, // fov
	rd_extract_double_scalar, // ratio
	rd_extract_double_vector, // color
	NULL,
};

static const t_element_info_extractor	g_pyramidlight_extractors[] = {
	rd_extract_double_vector, // posiiton
	rd_extract_double_vector, // direction
	rd_extract_double_scalar, // fovu
	rd_extract_double_scalar, // fovv
	rd_extract_double_scalar, // role
	rd_extract_double_scalar, // ratio
	rd_extract_double_vector, // color
	rd_extract_string, // xpm
	NULL,
};

static const t_element_info_extractor	g_texture_extractors[] = {
	rd_extract_string, // xpm_file_path
	rd_extract_double_scalar, // freq_u
	rd_extract_double_scalar, // freq_v
	NULL,
};

static const t_element_info_extractor	g_checker_extractors[] = {
	rd_extract_double_scalar, // freq_u
	rd_extract_double_scalar, // freq_v
	rd_extract_double_vector, // color
	rd_extract_double_vector, // subcolor
	NULL,
};

static const t_element_info_extractor	g_bumpmap_extractors[] = {
	rd_extract_string, // xpm_file_path
	rd_extract_double_scalar, // height
	rd_extract_double_scalar, // freq_u
	rd_extract_double_scalar, // freq_v
	NULL,
};

static const t_element_info_extractor	g_material_extractors[] = {
	rd_extract_double_scalar, // k_diffuse
	rd_extract_double_scalar, // k_specular
	rd_extract_double_scalar, // gloss
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
	g_paraboloid_extractors,
	g_cone_extractors,
	g_spotlight_extractors,
	g_pyramidlight_extractors,
	g_texture_extractors,
	g_checker_extractors,
	g_bumpmap_extractors,
	g_material_extractors,
};

t_element	*rd_extract_element(
	t_element_type etype,
	const char **words)
{
	t_element	*el;
	void		*fields[40];
	void		**fs;

	el = (t_element *)ft_calloc(1, sizeof(t_element));
	if (!el)
		return (NULL);
	el->etype = etype;
	fs = rd_get_element_slots(fields, el);
	if (!fs || !extract_seq(words, g_list_of_extractors[el->etype], fs))
	{
		rd_destroy_element(el);
		return (NULL);
	}
	rt_after_extraction(el);
	return (el);
}

// destroy all fields(excepts image) of a element and itself
void	rd_destroy_element(t_element *el)
{
	if (!el)
		return ;
	if (el->tex_el)
		rd_destroy_element(el->tex_el);
	if (el->bump_el)
		rd_destroy_element(el->bump_el);
	if (el->xpm_file_path)
		free(el->xpm_file_path);
	free(el);
}

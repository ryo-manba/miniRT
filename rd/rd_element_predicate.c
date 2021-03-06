/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_element_predicate.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 11:36:19 by corvvs            #+#    #+#             */
/*   Updated: 2022/01/17 11:56:24 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rd_read.h"

static const t_element_info_predicate	g_ambient_predicates[] = {
	rd_word_is_ratio,
	rd_word_is_color_vector,
	NULL};

static const t_element_info_predicate	g_camera_predicates[] = {
	rd_word_is_vector,
	rd_word_is_unit_vector,
	rd_word_is_fov_angle,
	NULL};

static const t_element_info_predicate	g_light_predicates[] = {
	rd_word_is_vector,
	rd_word_is_ratio,
	rd_word_is_color_vector,
	NULL};

static const t_element_info_predicate	g_sphere_predicates[] = {
	rd_word_is_vector,
	rd_word_is_positive_real,
	rd_word_is_color_vector,
	NULL};

static const t_element_info_predicate	g_plane_predicates[] = {
	rd_word_is_vector,
	rd_word_is_unit_vector,
	rd_word_is_color_vector,
	NULL};

static const t_element_info_predicate	g_cylinder_predicates[] = {
	rd_word_is_vector,
	rd_word_is_unit_vector,
	rd_word_is_positive_real,
	rd_word_is_positive_real,
	rd_word_is_color_vector,
	NULL};

static const t_element_info_predicate	g_paraboloid_predicates[] = {
	rd_word_is_vector,
	rd_word_is_vector,
	rd_word_is_unit_vector,
	rd_word_is_color_vector,
	NULL};

static const t_element_info_predicate	g_cone_predicates[] = {
	rd_word_is_vector,
	rd_word_is_unit_vector,
	rd_word_is_fov_angle,
	rd_word_is_color_vector,
	NULL};

static const t_element_info_predicate	g_spotlight_predicates[] = {
	rd_word_is_vector,
	rd_word_is_unit_vector,
	rd_word_is_fov_angle,
	rd_word_is_ratio,
	rd_word_is_color_vector,
	NULL};

static const t_element_info_predicate	g_pyramidlight_predicates[] = {
	rd_word_is_vector,
	rd_word_is_unit_vector,
	rd_word_is_fov_angle,
	rd_word_is_fov_angle,
	rd_word_is_role_angle,
	rd_word_is_ratio,
	rd_word_is_xpm_file_path,
	NULL};

static const t_element_info_predicate	g_sunlight_predicates[] = {
	rd_word_is_unit_vector,
	rd_word_is_ratio,
	rd_word_is_color_vector,
	NULL};

static const t_element_info_predicate	g_texture_predicates[] = {
	rd_word_is_xpm_file_path,
	rd_word_is_positive_real,
	rd_word_is_positive_real,
	NULL};

static const t_element_info_predicate	g_checker_predicates[] = {
	rd_word_is_positive_real,
	rd_word_is_positive_real,
	rd_word_is_color_vector,
	rd_word_is_color_vector,
	NULL};

static const t_element_info_predicate	g_bumpmap_predicates[] = {
	rd_word_is_xpm_file_path,
	rd_word_is_positive_real,
	rd_word_is_positive_real,
	rd_word_is_positive_real,
	NULL};

static const t_element_info_predicate	g_material_predicates[] = {
	rd_word_is_positive_real,
	rd_word_is_positive_real,
	rd_word_is_positive_real,
	NULL};

static const t_element_info_predicate	*g_element_predicate_array[] = {
	g_ambient_predicates,
	g_camera_predicates,
	g_light_predicates,
	g_sphere_predicates,
	g_plane_predicates,
	g_cylinder_predicates,
	g_paraboloid_predicates,
	g_cone_predicates,
	g_spotlight_predicates,
	g_pyramidlight_predicates,
	g_sunlight_predicates,
	g_texture_predicates,
	g_checker_predicates,
	g_bumpmap_predicates,
	g_material_predicates,
	NULL};

static const char						*g_element_ids[] = {
	RD_ID_AMBIENT,
	RD_ID_CAMERA,
	RD_ID_LIGHT,
	RD_ID_SPHERE,
	RD_ID_PLANE,
	RD_ID_CYLINDER,
	RD_ID_PARABOLOID,
	RD_ID_CONE,
	RD_ID_SPOTLIGHT,
	RD_ID_PYRAMIDLIGHT,
	RD_ID_SUNLIGHT,
	RD_ID_TEXTURE,
	RD_ID_CHECKER,
	RD_ID_BUMPMAP,
	RD_ID_MATERIAL,
	NULL};

static const t_element_type				g_element_types[] = {
	RD_ET_AMBIENT,
	RD_ET_CAMERA,
	RD_ET_LIGHT,
	RD_ET_SPHERE,
	RD_ET_PLANE,
	RD_ET_CYLINDER,
	RD_ET_PARABOLOID,
	RD_ET_CONE,
	RD_ET_SPOTLIGHT,
	RD_ET_PYRAMIDLIGHT,
	RD_ET_SUNLIGHT,
	RD_ET_TEXTURE,
	RD_ET_CHECKER,
	RD_ET_BUMPMAP,
	RD_ET_MATERIAL,
	RD_ET_DUMMY};

static t_element_type	print_and_quit(t_temp_scene *scene, const char *error)
{
	rd_print_error_cur(&scene->cur, error);
	return (RD_ET_UNEXPECTED);
}

static t_element_type	matches_predicates(
	t_element_type expected_type,
	t_temp_scene *scene,
	const char **words,
	const t_element_info_predicate *predicates)
{
	scene->cur.word_number = 0;
	if (!words)
	{
		return (RD_ET_UNEXPECTED);
	}
	while (words[scene->cur.word_number + 1])
	{
		if (!predicates[scene->cur.word_number])
			return (print_and_quit(scene, "excess words"));
		if (!(predicates[scene->cur.word_number])(
			&scene->cur, words[scene->cur.word_number + 1]))
			return (RD_ET_UNEXPECTED);
		scene->cur.word_number += 1;
	}
	if (predicates[scene->cur.word_number])
		return (print_and_quit(scene, "less words"));
	scene->cur.word_number = 0;
	return (expected_type);
}

t_element_type	rd_detect_element_type(t_temp_scene *scene, const char **words)
{
	size_t			i;

	scene->cur.symbol = NULL;
	if (!words)
		return (print_and_quit(scene, "no words"));
	scene->cur.symbol = (char *)words[0];
	scene->cur.word_number = 0;
	i = 0;
	while (g_element_ids[i])
	{
		if (ft_strcmp(scene->cur.symbol, g_element_ids[i]) == 0)
			return (matches_predicates(g_element_types[i], scene, words,
					g_element_predicate_array[i]));
		i += 1;
	}
	return (print_and_quit(scene, "no element for given identifier"));
}

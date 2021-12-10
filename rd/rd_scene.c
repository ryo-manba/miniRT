/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_scene.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 15:02:57 by corvvs            #+#    #+#             */
/*   Updated: 2021/12/10 19:43:36 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rd_read.h"

static void	element_addback(t_element **list, t_element *el)
{
	t_element	*temp;

	if (*list)
	{
		temp = *list;
		while (temp->next)
			temp = temp->next;
		temp->next = el;
	}
	else
		*list = el;
}

static t_element	*element_from_words(t_temp_scene *scene, const char **words)
{
	t_element		*el;
	t_element_type	etype;

	etype = rd_detect_element_type(scene, words);
	if (etype == RD_ET_UNEXPECTED)
		return (NULL);
	if (etype == RD_ET_AMBIENT && scene->ambient)
	{
		rd_print_error_cur(&scene->cur, "found 2nd ambient");
		return (NULL);
	}
	if (etype == RD_ET_CAMERA && scene->camera)
	{
		rd_print_error_cur(&scene->cur, "found 2nd camera");
		return (NULL);
	}
	if (etype == RD_ET_LIGHT && scene->light_list)
	{
		rd_print_error_cur(&scene->cur, "found 2nd light");
		return (NULL);
	}
	el = rd_extract_element(etype, words);
	if (!el)
		rd_print_error_cur(&scene->cur, "failed to extract an element");
	return (el);
}

static bool	list_to_array(t_element *list, size_t *n_ptr, t_element ***array)
{
	t_element	*el;
	size_t		i;

	el = list;
	while (el)
	{
		*n_ptr += 1;
		el = el->next;
	}
	*array = (t_element **)ft_calloc(*n_ptr + 1, sizeof(t_element *));
	if (!*array)
		return (false);
	i = 0;
	el = list;
	while (el)
	{
		(*array)[i] = el;
		i += 1;
		el = el->next;
	}
	return (true);
}

bool	rd_read_scene(const char *filename, t_scene *scene)
{
	t_temp_scene	temp_scene;
	char			*content;
	char			**lines;
	char			**words;
	t_element		*el;

	content = rd_read_file_content(filename);
	if (!content)
		return (rd_print_error("failed to read file content"));
	lines = ft_split(content, '\n');
	free(content);
	if (!lines)
		return (rd_print_error("failed to split content"));
	ft_bzero(&temp_scene, sizeof(t_temp_scene));
	temp_scene.cur.line_number = 0;
	while (lines[temp_scene.cur.line_number])
	{
		words = ft_split(lines[temp_scene.cur.line_number], ' ');
		el = element_from_words(&temp_scene, (const char **)words);
		rd_free_strarray(words);
		if (!el)
		{
			rd_free_strarray(lines);
			return (false);
		}
		el->id = temp_scene.cur.line_number + 1;
		if (el->etype == RD_ET_AMBIENT)
			temp_scene.ambient = el;
		else if (el->etype == RD_ET_CAMERA)
			temp_scene.camera = el;
		else if (el->etype == RD_ET_LIGHT)
			element_addback(&temp_scene.light_list, el);
		else
			element_addback(&temp_scene.object_list, el);
		temp_scene.cur.line_number += 1;
	}
	rd_free_strarray(lines);
	if (!temp_scene.ambient)
		return (rd_print_error("ambient not found"));
	if (!temp_scene.camera)
		return (rd_print_error("camera not found"));
	if (!temp_scene.light_list)
		return (rd_print_error("light not found"));
	ft_bzero(scene, sizeof(t_scene));
	list_to_array(temp_scene.light_list, &scene->n_lights, &scene->lights);
	list_to_array(temp_scene.object_list, &scene->n_objects, &scene->objects);
	scene->ambient = temp_scene.ambient;
	scene->camera = temp_scene.camera;
	return (true);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_scene.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 15:02:57 by corvvs            #+#    #+#             */
/*   Updated: 2022/01/10 09:32:38 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rd_read.h"

static void	element_addback(t_element **list, t_element *el)
{
	t_element	*temp;

	printf("%p <- %p(%d), %p\n", list, el, el->etype, el->next);
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

static bool	attach_attribute(t_temp_scene *scene, t_element **list, t_element *el)
{
	t_element	*tail;

	printf("[%s]\n", scene->cur.symbol);
	if (!*list)
		return (rd_print_error_cur(&scene->cur, "no object"));
	tail = *list;
	while (tail->next)
		tail = tail->next;
	if (el->etype == RD_ET_TEXTURE || el->etype == RD_ET_CHECKER)
	{
		if (tail->tex_el)
			return (rd_print_error_cur(&scene->cur, "texture already attached"));
		tail->tex_el = el;
	}
	else if (el->etype == RD_ET_BUMPMAP)
	{
		if (tail->bump_el)
			return (rd_print_error_cur(&scene->cur, "bumpmap already attached"));
		tail->bump_el = el;
	}
	else if (el->etype == RD_ET_MATERIAL)
	{
		tail->gloss = el->gloss;
		rd_destroy_element(el);
	}
	return (true);
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
	printf("etype: %d\n", el->etype);
	if (!el)
		rd_print_error_cur(&scene->cur, "failed to extract an element");
	return (el);
}

static bool	list_to_array(t_element *list, size_t *n_ptr, t_element ***array)
{
	t_element	*el;
	size_t		i;

	el = list;
	printf("els: %p\n", el);
	while (el)
	{
		*n_ptr += 1;
		printf("el: %p\n", el);
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
		if (!el)
		{
			rd_free_strarray(words);
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
		else if (el->etype == RD_ET_SPOTLIGHT)
			element_addback(&temp_scene.spotlight_list, el);
		else if (el->etype == RD_ET_TEXTURE || el->etype == RD_ET_CHECKER
			|| el->etype == RD_ET_BUMPMAP || el->etype == RD_ET_MATERIAL)
			{
				if (!attach_attribute(&temp_scene, &temp_scene.object_list, el))
				{
					rd_free_strarray(words);
					rd_free_strarray(lines);
					return (false);
				}
			}
		else
			element_addback(&temp_scene.object_list, el);
		temp_scene.cur.line_number += 1;
		rd_free_strarray(words);
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
	list_to_array(temp_scene.spotlight_list, &scene->n_spotlights, &scene->spotlights);
	scene->ambient = temp_scene.ambient;
	scene->camera = temp_scene.camera;
	return (true);
}

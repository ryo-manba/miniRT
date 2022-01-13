/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_scene.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 15:02:57 by corvvs            #+#    #+#             */
/*   Updated: 2022/01/13 14:34:10 by corvvs           ###   ########.fr       */
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

	el = NULL;
	etype = rd_detect_element_type(scene, words);
	if (etype == RD_ET_UNEXPECTED)
		return (NULL);
	else if (etype == RD_ET_AMBIENT && scene->ambient)
		rd_print_error_cur(&scene->cur, "found 2nd ambient");
	else if (etype == RD_ET_CAMERA && scene->camera)
		rd_print_error_cur(&scene->cur, "found 2nd camera");
	else if (etype == RD_ET_LIGHT && scene->light_list)
		rd_print_error_cur(&scene->cur, "found 2nd light");
	else
	{
		el = rd_extract_element(etype, words);
		if (!el)
			rd_print_error_cur(&scene->cur, "failed to extract an element");
	}
	return (el);
}

static bool	assimilate_element(
	t_temp_scene *temp_scene)
{
	if (temp_scene->el->etype == RD_ET_AMBIENT)
		temp_scene->ambient = temp_scene->el;
	else if (temp_scene->el->etype == RD_ET_CAMERA)
		temp_scene->camera = temp_scene->el;
	else if (temp_scene->el->etype == RD_ET_TEXTURE
		|| temp_scene->el->etype == RD_ET_CHECKER
		|| temp_scene->el->etype == RD_ET_BUMPMAP
		|| temp_scene->el->etype == RD_ET_MATERIAL)
	{
		if (!rd_attach_attribute(temp_scene,
				&temp_scene->object_list, temp_scene->el))
			return (false);
	}
	else if (temp_scene->el->etype == RD_ET_LIGHT)
		element_addback(&temp_scene->light_list, temp_scene->el);
	else if (temp_scene->el->etype == RD_ET_SPOTLIGHT)
		element_addback(&temp_scene->spotlight_list, temp_scene->el);
	else
		element_addback(&temp_scene->object_list, temp_scene->el);
	return (true);
}

static void	next_line(t_temp_scene *temp_scene)
{
	rd_free_strarray(&temp_scene->words);
	temp_scene->el = NULL;
	temp_scene->cur.line_number += 1;
}

bool	rd_read_scene(const char *filename, t_scene *scene)
{
	t_temp_scene	temp_scene;

	ft_bzero(&temp_scene, sizeof(t_temp_scene));
	temp_scene.content = rd_read_file_content(filename);
	if (!temp_scene.content)
		return (rd_print_error("failed to read file content", &temp_scene));
	temp_scene.lines = ft_split(temp_scene.content, '\n');
	if (!temp_scene.lines)
		return (rd_print_error("failed to split content", &temp_scene));
	temp_scene.cur.line_number = 0;
	while (temp_scene.lines[temp_scene.cur.line_number])
	{
		temp_scene.words
			= ft_split(temp_scene.lines[temp_scene.cur.line_number], ' ');
		if (!temp_scene.words)
			return (rd_print_error("failed to split line", &temp_scene));
		temp_scene.el
			= element_from_words(&temp_scene, (const char **)temp_scene.words);
		if (!temp_scene.el)
			return (rd_destroy_temp_scene_and_quit(&temp_scene));
		if (!assimilate_element(&temp_scene))
			return (rd_destroy_temp_scene_and_quit(&temp_scene));
		next_line(&temp_scene);
	}
	return (rd_after_read(&temp_scene, scene));
}

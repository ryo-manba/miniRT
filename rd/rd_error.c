/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 15:05:37 by corvvs            #+#    #+#             */
/*   Updated: 2022/01/11 19:07:13 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rd_read.h"

bool	rd_print_error(const char *error, t_temp_scene *temp_scene)
{
	printf("\e[93mError\n%s\e[m\n", error);
	if (temp_scene)
		rd_destroy_temp_scene_fail(temp_scene);
	return (false);
}

bool	rd_print_error_cur(t_file_cursor *cur, const char *error)
{
	(void)cur;
	printf("\e[93mError(element: %zu", cur->line_number);
	if (cur->symbol)
	{
		printf(", symbol: %s", cur->symbol);
		if (cur->word_number)
		{
			printf(", word: %zu", cur->word_number);
		}
	}
	printf(") %s\e[m\n", error);
	return (false);
}

bool	rd_destroy_temp_scene_and_quit(t_temp_scene *temp_scene)
{
	if (temp_scene)
		rd_destroy_temp_scene_fail(temp_scene);
	return (false);
}

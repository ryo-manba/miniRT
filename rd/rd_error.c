/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 15:05:37 by corvvs            #+#    #+#             */
/*   Updated: 2021/12/09 10:12:44 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rd_read.h"

bool	rd_print_error(const char *error)
{
	printf("Error: %s\n", error);
	return (false);
}

bool	rd_print_error_cur(t_file_cursor *cur, const char *error)
{
	(void)cur;
	printf("Error(element: %zu", cur->line_number);
	if (cur->symbol)
	{
		printf(", symbol: %s", cur->symbol);
		if (cur->word_number)
		{
			printf(", word: %zu", cur->word_number);
		}
	}
	printf(") %s\n", error);
	return (false);
}

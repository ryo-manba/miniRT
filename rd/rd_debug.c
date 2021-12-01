/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_debug.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 11:36:13 by corvvs            #+#    #+#             */
/*   Updated: 2021/12/01 12:01:35 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rd_read.h"

void	debug_rd_print_words(char *words[])
{
	while (*words)
	{
		printf("[%s] ", *words);
		words += 1;
	}
	printf("\n");
}

void	debug_rd_print_vector(t_vec3 *vec)
{
	printf("(%f, %f, %f)", vec->x, vec->y, vec->z);
}

void	debug_rd_print_element(t_element *element)
{
	printf("{");
	printf(" position: "); debug_rd_print_vector(&element->position);
	printf(" direction: "); debug_rd_print_vector(&element->direction);
	printf(" ratio: %f", element->ratio);
	printf(" radius: %f", element->radius);
	printf(" diameter: %f", element->diameter);
	printf(" height: %f", element->height);
	printf(" color: "); debug_rd_print_vector(&element->color);
	printf("}\n");
}

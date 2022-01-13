/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_endswith.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 19:30:29 by corvvs            #+#    #+#             */
/*   Updated: 2022/01/13 19:57:17 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	ft_str_endswith(const char *str, const char *suffix)
{
	size_t	n_str;
	size_t	n_suffix;

	if (!str || !suffix)
		return (false);
	n_str = ft_strlen(str);
	n_suffix = ft_strlen(suffix);
	if (n_str < n_suffix)
		return (false);
	return (ft_strcmp(str + (n_str - n_suffix), suffix) == 0);
}

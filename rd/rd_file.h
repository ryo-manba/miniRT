/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_file.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 11:37:12 by corvvs            #+#    #+#             */
/*   Updated: 2021/12/01 14:23:16 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RD_FILE_H
# define RD_FILE_H

# include <unistd.h>
# include <fcntl.h>
# include <stdbool.h>
# include "../libft/libft.h"
# define FT_BUFSIZ 4096

typedef struct s_plastic_buffer
{
	char	*body;
	size_t	cap;
	size_t	used;
}	t_plastic_buffer;

#endif

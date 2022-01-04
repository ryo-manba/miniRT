/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   co_image_structure.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 20:08:35 by corvvs            #+#    #+#             */
/*   Updated: 2021/12/27 20:09:03 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CO_IMAGE_STRUCTURE_H
# define CO_IMAGE_STRUCTURE_H

typedef struct s_img {
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}			t_img;

#endif

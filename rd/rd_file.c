/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_file.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 11:36:10 by corvvs            #+#    #+#             */
/*   Updated: 2022/01/13 20:00:39 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rd_file.h"

static void	*quit_with_error(const char *error)
{
	printf("\e[93mError\n%s\e[m\n", error);
	return (NULL);
}

static void	deploy_buffer(t_plastic_buffer *buffer)
{
	char	*new_body;

	if (buffer->cap > 0)
		buffer->cap = buffer->cap * 2;
	else
		buffer->cap = FT_BUFSIZ;
	new_body = (char *)malloc((buffer->cap + 1) * sizeof(char));
	if (!new_body)
	{
		free(buffer->body);
		return ;
	}
	if (new_body)
	{
		ft_memcpy(new_body, buffer->body, buffer->used);
		free(buffer->body);
	}
	buffer->body = new_body;
}

static char	*read_from_fd(const int fd)
{
	char				read_buf[FT_BUFSIZ];
	ssize_t				read_size;
	t_plastic_buffer	data_buf;

	ft_bzero(&data_buf, sizeof(t_plastic_buffer));
	while (1)
	{
		read_size = read(fd, read_buf, FT_BUFSIZ);
		if (read_size <= 0)
			break ;
		if (data_buf.used + read_size > data_buf.cap)
			deploy_buffer(&data_buf);
		if (!data_buf.body)
			return (NULL);
		ft_memcpy(data_buf.body + data_buf.used, read_buf, read_size);
		data_buf.used += read_size;
	}
	if (read_size < 0 || !data_buf.body)
	{
		free(data_buf.body);
		return (NULL);
	}
	data_buf.body[data_buf.used] = '\0';
	return (data_buf.body);
}

char	*rd_read_file_content(const char *filename)
{
	int		fd;
	char	*content;

	if (!ft_str_endswith(filename, ".rt"))
		return (quit_with_error("extension is not rt"));
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (quit_with_error("failed to open file"));
	content = read_from_fd(fd);
	if (!content)
		return (quit_with_error("failed to read file content"));
	if (close(fd) == -1)
	{
		free(content);
		return (quit_with_error("failed to close file"));
	}
	return (content);
}

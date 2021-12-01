#include "rd_read.h"

static void	deploy_buffer(t_plastic_buffer* buffer)
{
	buffer->cap = buffer->cap > 0 ? buffer->cap * 2 : FT_BUFSIZ;
	char *new_body = (char *)malloc((buffer->cap + 1) * sizeof(char));
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
	while ((read_size = read(fd, read_buf, FT_BUFSIZ)) > 0)
	{
		if (data_buf.used + read_size > data_buf.cap)
		{
			deploy_buffer(&data_buf);
		}
		if (!data_buf.body)
		{
			return (NULL);
		}
		ft_memcpy(data_buf.body + data_buf.used, read_buf, read_size);
		data_buf.used += read_size;
	}
	if (!data_buf.body)
	{
		return (NULL);
	}
	data_buf.body[data_buf.used] = '\0';
	return (data_buf.body);
}


char	*rd_read_file_content(const char* filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		return (NULL);
	}
	char *content = read_from_fd(fd);
	close(fd);
	return (content);
}

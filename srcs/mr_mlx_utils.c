#include "minirt.h"

void	mr_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

unsigned int	mr_mlx_pixel_get(t_img *img, int x, int y)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	return *(unsigned int *)dst;
}

int	mr_exit_window(t_info *info)
{
	mlx_destroy_window(info->mlx, info->win);
	exit(0);
}

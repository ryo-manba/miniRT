#include "minirt.h"

void	mr_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

int	mr_exit_window(t_info *info)
{
	mlx_destroy_window(info->mlx, info->win);
	exit(0);
}

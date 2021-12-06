#ifndef MR_CAMERA_H
# define MR_CAMERA_H

typedef struct s_viewport
{
	t_camera	camera;
	double		vp_height;
	double		vp_width;
	double		focal_length;
	t_vec3		screen_center;
}	t_viewport;

#endif

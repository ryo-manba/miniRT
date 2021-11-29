#ifndef RT_SCENE_H
# define RT_SCENE_H

#include "mr_vec3.h"
// mr -> main, hook
// rt -> raytracing
// read, rendaring, others

typedef struct s_img {
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}			t_img;

typedef struct s_rgb {
	int	r;
	int	g;
	int	b;
}	t_rgb;

typedef struct s_info
{
	void	*mlx;
	void	*win;
	t_img	img;
} t_info;

typedef enum e_objects_type
{
	E_PLANE,
	E_SPHERE,
	E_CYLINDER
} t_objects_type;

// sphere, plane, Cylinder
typedef struct s_object
{
	t_vec3			coodinates;
	t_rgb			rgb;
	t_objects_type	type;			// Plane, Sphere, Cylinder
	t_vec3			direction_vec; 	// Plane,  Cylinder : 3D正規化された方位ベクトル(x,y,z),[-1,1]
	double			diameter;	 	// Sphere, Cylinder : 直径
	double			height;			// Cylinder			: 円柱の高さ
} t_object;

typedef struct	s_camera
{
	t_vec3	coodinates;
	t_rgb	rgb;
	int		fov; // 視野角[0,180]
} t_camera;

typedef struct	s_ray
{
	t_vec3	origin;
	t_vec3	direction;
} t_ray;

#endif

#ifndef VEC3_H
# define VEC3_H

typedef struct	vec3
{
	double x;
	double y;
	double z;
} t_vec3;

t_vec3	vec3_add(t_vec3 u, t_vec3 v);
t_vec3	vec3_sub(t_vec3 u, t_vec3 v);
t_vec3	vec3_mul(t_vec3 u, t_vec3 v);
double	vec3_dot(t_vec3 u, t_vec3 v);
t_vec3	vec3_cross(t_vec3 u, t_vec3 v);

double	vec3_length_squared(t_vec3 v);
double	vec3_length(t_vec3 v);
t_vec3	vec3_mul_double(t_vec3 u, double t);
t_vec3	vec3_div_double(t_vec3 v, double t);
t_vec3	unit_vector(t_vec3 v);

#endif

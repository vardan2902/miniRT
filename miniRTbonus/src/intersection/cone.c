#include <minirt.h>

bool	intersect_cone(t_ray *ray, t_object *object, t_hit *hit)
{
    t_cone      *cone = (t_cone *)object->object;
	t_vector	co = v_sub(*ray->position, *cone->position);
	t_vector	normal_orient = v_normalize(*cone->orientation);

	float		k = (cone->diameter / 2) / cone->height;
	float		k2 = k * k;

	float		d_dot_v = v_dot_product(*ray->orientation, normal_orient);
	float		co_dot_v = v_dot_product(co, normal_orient);

	t_vector	d_proj = v_sub(*ray->orientation, v_scalar_product(normal_orient, d_dot_v));
	t_vector	co_proj = v_sub(co, v_scalar_product(normal_orient, co_dot_v));

	float		a = v_dot_product(d_proj, d_proj) - k2 * d_dot_v * d_dot_v;
	float		b = 2 * (v_dot_product(d_proj, co_proj) - k2 * d_dot_v * co_dot_v);
	float		c = v_dot_product(co_proj, co_proj) - k2 * co_dot_v * co_dot_v;

	float		discriminant = b * b - 4 * a * c;
	if (discriminant < 0.0f)
		return (false);

	float		sqrt_d = sqrtf(discriminant);
	float		t0 = (-b - sqrt_d) / (2 * a);
	float		t1 = (-b + sqrt_d) / (2 * a);
	float		t_local = fminf(t0, t1);

	if (t_local < EPSILON)
		t_local = fmaxf(t0, t1);
	if (t_local < EPSILON || t_local >= hit->t)
		return (false);    

	t_vector	p = v_add(*ray->position, v_scalar_product(*ray->orientation, t_local));
	t_vector	apex_to_p = v_sub(p, *cone->position);
	float		h_proj = v_dot_product(apex_to_p, normal_orient);

	if (h_proj < 0.0f || h_proj > cone->height)
		return (false);

	hit->t = t_local;
	hit->position = p;

	t_vector	tmp = v_scalar_product(normal_orient, v_dot_product(apex_to_p, normal_orient));
	t_vector	proj = v_sub(apex_to_p, tmp);
	float		m = sqrtf(proj.x * proj.x + proj.y * proj.y + proj.z * proj.z);
	float		slope = (cone->diameter / 2) / cone->height;
	t_vector	n = v_normalize(v_sub(apex_to_p, v_scalar_product(normal_orient, m / slope)));
	hit->orientation = v_normalize(n);
	hit->object = object;
	return (true);
}

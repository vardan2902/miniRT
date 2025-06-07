#include <minirt.h>

static t_rgb get_checker_color_plane(t_vector point, t_plane *plane, float size)
{
	t_vector normal = v_normalize(*plane->orientation);

	t_vector ref = (fabs(normal.y) < 0.999f) ? (t_vector){0, 1, 0} : (t_vector){1, 0, 0};
	t_vector u_axis = v_normalize(v_cross_product(ref, normal));
	t_vector v_axis = v_cross_product(normal, u_axis);

	t_vector p = v_sub(point, *plane->position);

	float u = v_dot_product(p, u_axis);
	float v = v_dot_product(p, v_axis);

	int u_check = floor(u / size);
	int v_check = floor(v / size);

	if ((u_check + v_check) % 2 == 0)
		return (t_rgb){255, 255, 255};
	else
		return (t_rgb){0, 0, 0};
}


static t_rgb get_checker_color_sphere(t_vector point, t_sphere *sphere, float size)
{
	t_vector p = v_sub(point, *sphere->position);

	float theta = atan2(p.z, p.x);
	float phi = acos(p.y / (sphere->diameter / 2));

	float u = (theta + M_PI) / (2 * M_PI);
	float v = phi / M_PI;

	int u_check = floor(u * size);
	int v_check = floor(v * size);

	if ((u_check + v_check) % 2 == 0)
		return (t_rgb){255, 255, 255};
	else
		return (t_rgb){0, 0, 0};
}

static t_rgb get_checker_color_cylinder(t_vector point, t_cylinder *cyl, float size)
{
	t_vector p = v_sub(point, *cyl->position);

	t_vector axis = v_normalize(*cyl->orientation);
	t_vector proj = v_sub(p, v_scalar_product(axis, v_dot_product(p, axis)));

	float theta = atan2(proj.z, proj.x);
	float height = v_dot_product(p, axis);

	float u = (theta + M_PI) / (2 * M_PI);
	float v = height / cyl->height + 0.5f;

	int u_check = floor(u * size);
	int v_check = floor(v * size);

	if ((u_check + v_check) % 2 == 0)
		return (t_rgb){255, 255, 255};
	else
		return (t_rgb){0, 0, 0};
}

static t_rgb	get_checker_color_cone(t_vector point, t_cone *cone, float size)
{
	t_vector	v = v_normalize(*cone->orientation);
	t_vector	hit_vec = v_sub(point, *cone->position);

	float height = v_dot_product(hit_vec, v);
	float v_val = height / cone->height;

	t_vector around = v_sub(hit_vec, v_scalar_product(v, height));
	t_vector ref = {1, 0, 0};

	t_vector u_axis = v_normalize(v_cross_product(v, ref));
	if (v_length(u_axis) == 0)
		u_axis = (t_vector){0, 0, 1};
	t_vector w_axis = v_normalize(v_cross_product(v, u_axis));

	float x = v_dot_product(around, u_axis);
	float y = v_dot_product(around, w_axis);
	float theta = atan2f(y, x);
	if (theta < 0)
		theta += 2 * M_PI;

	float u_val = theta / (2 * M_PI);

	int	u_check = (int)(u_val * size);
	int	v_check = (int)(v_val * size);

	if ((u_check + v_check) % 2 == 0)
		return ((t_rgb){255, 255, 255});
	return ((t_rgb){0, 0, 0});
}

t_rgb get_checker_color(t_vector point, t_object *object)
{
	if (object->type == E_PLANE)
		return (get_checker_color_plane(point, (t_plane *)object->object, 10.0f));
	else if (object->type == E_SPHERE)
		return (get_checker_color_sphere(point, (t_sphere *)object->object, 6.0f));
	else if (object->type == E_CYLINDER)
		return (get_checker_color_cylinder(point, (t_cylinder *)object->object, 6.0f));
	else if (object->type == E_CONE)
		return (get_checker_color_cone(point, (t_cone *)object->object, 6.0f));
	return (t_rgb){0, 0, 0};
}
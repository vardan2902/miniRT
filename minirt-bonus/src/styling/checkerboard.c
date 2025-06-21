/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkerboard.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 16:19:29 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/06/21 16:34:08 by ysaroyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static t_rgb	get_checker_color_plane(t_vector point,
		t_plane *plane, float size)
{
	t_vector	normal;
	t_vector	ref;
	t_vector	u_axis;
	int			u_check;
	int			v_check;

	normal = v_normalize(*plane->orientation);
	if (fabs(normal.y) < 0.999f)
		ref = (t_vector){0, 1, 0};
	else
		ref = (t_vector){1, 0, 0};
	u_axis = v_normalize(v_cross_product(ref, normal));
	u_check = floor(v_dot_product(v_sub(point, *plane->position),
				u_axis) / size);
	v_check = floor(v_dot_product(v_sub(point, *plane->position),
				v_cross_product(normal, u_axis)) / size);
	if ((u_check + v_check) % 2 == 0)
		return ((t_rgb){255, 255, 255});
	else
		return ((t_rgb){0, 0, 0});
}

static t_rgb	get_checker_color_sphere(t_vector point,
		t_sphere *sphere, float size)
{
	t_vector	p;
	float		u;
	float		v;
	int			u_check;
	int			v_check;

	p = v_sub(point, *sphere->position);
	u = (atan2(p.z, p.x) + M_PI) / (2 * M_PI);
	v = acos(p.y / (sphere->diameter / 2)) / M_PI;
	u_check = floor(u * size);
	v_check = floor(v * size);
	if ((u_check + v_check) % 2 == 0)
		return ((t_rgb){255, 255, 255});
	else
		return ((t_rgb){0, 0, 0});
}

static t_rgb	get_checker_color_cylinder(t_vector point,
		t_cylinder *cyl, float size)
{
	t_vector	p;
	t_vector	axis;
	t_vector	proj;
	int			u_check;
	int			v_check;

	p = v_sub(point, *cyl->position);
	axis = v_normalize(*cyl->orientation);
	proj = v_sub(p, v_scalar_product(axis, v_dot_product(p, axis)));
	u_check = floor((atan2(proj.z, proj.x) + M_PI) / (2 * M_PI) * size);
	v_check = floor(v_dot_product(p, axis) / cyl->height + 0.5f * size);
	if ((u_check + v_check) % 2 == 0)
		return ((t_rgb){255, 255, 255});
	else
		return ((t_rgb){0, 0, 0});
}

static t_rgb	get_checker_color_cone(t_vector point, t_cone *cone, float size)
{
	t_vector	v;
	float		height;
	t_vector	around;
	t_vector	u_axis;
	float		theta;

	v = v_normalize(*cone->orientation);
	height = v_dot_product(v_sub(point, *cone->position), v);
	around = v_sub(v_sub(point, *cone->position), v_scalar_product(v, height));
	u_axis = v_normalize(v_cross_product(v, (t_vector){1, 0, 0}));
	if (v_length(u_axis) == 0)
		u_axis = (t_vector){0, 0, 1};
	theta = atan2f(v_dot_product(around, v_normalize(v_cross_product(v,
						u_axis))), v_dot_product(around, u_axis));
	if (theta < 0)
		theta += 2 * M_PI;
	if (((int)(theta / (2 * M_PI) * size)
		+ (int)(height / cone->height * size)) % 2 == 0)
		return ((t_rgb){255, 255, 255});
	return ((t_rgb){0, 0, 0});
}

t_rgb	get_checker_color(t_vector point, t_object *object)
{
	if (object->type == E_PLANE)
		return (get_checker_color_plane(point,
				(t_plane *)object->object, 10.0f));
	else if (object->type == E_SPHERE)
		return (get_checker_color_sphere(point,
				(t_sphere *)object->object, 6.0f));
	else if (object->type == E_CYLINDER)
		return (get_checker_color_cylinder(point,
				(t_cylinder *)object->object, 6.0f));
	else if (object->type == E_CONE)
		return (get_checker_color_cone(point, (t_cone *)object->object, 6.0f));
	return ((t_rgb){0, 0, 0});
}

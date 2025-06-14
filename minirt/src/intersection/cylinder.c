/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 18:33:28 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/06/14 21:05:52 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static t_vector	compute_quadratic_parts(t_ray *ray, t_cylinder *cylinder,
	t_coefficients *coeff)
{
	t_vector	oc;
	t_vector	a_part;
	t_vector	b_part;
	t_vector	axis;

	axis = v_normalize(*cylinder->orientation);
	oc = v_sub(*ray->position, *cylinder->position);
	a_part = v_sub(*ray->orientation, v_scalar_product(axis,
				v_dot_product(*ray->orientation, axis)));
	b_part = v_sub(oc, v_scalar_product(axis, v_dot_product(oc, axis)));
	coeff->a = v_dot_product(a_part, a_part);
	coeff->b = 2.0f * v_dot_product(a_part, b_part);
	coeff->c = v_dot_product(b_part, b_part)
		- powf(cylinder->diameter / 2.0f, 2);
	return (axis);
}

static bool	solve_quadratic(t_coefficients *coeff, t_cylinder_props *props)
{
	float	discriminant;
	float	tmp;

	discriminant = calculate_discriminant(coeff->a, coeff->b, coeff->c);
	if (discriminant < 0.0f)
		return (false);
	props->roots = calculate_hit(discriminant, coeff->a, coeff->b);
	if (props->roots.t1 > props->roots.t2)
	{
		tmp = props->roots.t1;
		props->roots.t1 = props->roots.t2;
		props->roots.t2 = tmp;
	}
	return (true);
}

static bool	valid_cylinder_hit(t_ray *ray, t_object *object,
	t_cylinder_props *props, float t)
{
	t_cylinder	*cylinder;
	t_vector	p;
	t_vector	cp;
	t_vector	normal;
	float		height_on_axis;

	cylinder = (t_cylinder *)object->object;
	if (t < 0.001f)
		return (false);
	p = v_add(*ray->position, v_scalar_product(*ray->orientation, t));
	cp = v_sub(p, *cylinder->position);
	height_on_axis = v_dot_product(cp, props->axis);
	if (height_on_axis >= 0.0f && height_on_axis <= cylinder->height)
	{
		props->side_hit.t = t;
		props->side_hit.position = v_scalar_product(p, 1);
		normal = v_normalize(v_sub(cp,
					v_scalar_product(props->axis, height_on_axis)));
		props->side_hit.orientation = normal;
		props->side_hit.object = object;
		return (true);
	}
	return (false);
}

bool	intersect_cylinder(t_ray *ray, t_object *object, t_hit *hit)
{
	t_cylinder			*cylinder;
	t_coefficients		coeff;
	t_cylinder_props	props;
	bool				intersection_found;

	props.side_ok = false;
	props.cap_ok = false;
	props.roots.t1 = 0;
	cylinder = (t_cylinder *)object->object;
	props.axis = compute_quadratic_parts(ray, cylinder, &coeff);
	if (solve_quadratic(&coeff, &props))
		props.side_ok = valid_cylinder_hit(ray, object, &props, props.roots.t1)
			|| valid_cylinder_hit(ray, object, &props, props.roots.t2);
	props.cap_ok = check_caps(ray, object, &props.cap_hit, props.axis);
	intersection_found = props.side_ok && (!props.cap_ok
			|| props.side_hit.t < props.cap_hit.t);
	if (intersection_found)
		*hit = props.side_hit;
	else if (props.cap_ok)
		*hit = props.cap_hit;
	if (props.roots.t1 < 0)
		hit->orientation = v_scalar_product(hit->orientation, -1.0f);
	return (intersection_found || props.cap_ok);
}

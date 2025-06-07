/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 18:33:28 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/06/07 17:16:14 by vapetros         ###   ########.fr       */
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
	float	sqrt_disc;
	float	tmp;

	discriminant = coeff->b * coeff->b - 4 * coeff->a * coeff->c;
	if (discriminant < 0.0f)
		return (false);
	sqrt_disc = sqrtf(discriminant);
	props->t0 = (-coeff->b - sqrt_disc) / (2.0f * coeff->a);
	props->t1 = (-coeff->b + sqrt_disc) / (2.0f * coeff->a);
	if (props->t0 > props->t1)
	{
		tmp = props->t0;
		props->t0 = props->t1;
		props->t1 = tmp;
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

	props.side_ok = false;
	props.cap_ok = false;
	cylinder = (t_cylinder *)object->object;
	props.axis = compute_quadratic_parts(ray, cylinder, &coeff);
	if (solve_quadratic(&coeff, &props))
	{
		props.side_ok = valid_cylinder_hit(ray, object, &props, props.t0)
			|| valid_cylinder_hit(ray, object, &props, props.t1);
	}
	props.cap_ok = check_caps(ray, object, &props.cap_hit, props.axis);
	if (props.side_ok && (!props.cap_ok || props.side_hit.t < props.cap_hit.t))
	{
		*hit = props.side_hit;
		return (true);
	}
	else if (props.cap_ok)
	{
		*hit = props.cap_hit;
		return (true);
	}
	return (false);
}

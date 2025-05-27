/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 18:33:28 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/05/01 17:46:13 by ysaroyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static t_vector	compute_quadratic_parts(t_ray *ray, t_cylinder *cylinder, t_coefficients *coeff)
{
	t_vector	oc;
	t_vector	a_part;
	t_vector	b_part;
	t_vector	axis;

	axis = v_normalize(*cylinder->orientation);
	oc = v_sub(*ray->position, *cylinder->position);
	a_part = v_sub(*ray->orientation, v_scalar_product(axis, v_dot_product(*ray->orientation, axis)));
	b_part = v_sub(oc, v_scalar_product(axis, v_dot_product(oc, axis)));
	coeff->a = v_dot_product(a_part, a_part);
	coeff->b = 2.0f * v_dot_product(a_part, b_part);
	coeff->c = v_dot_product(b_part, b_part) - powf(cylinder->diameter / 2.0f, 2);
	return (axis);
}

static bool	solve_quadratic(t_coefficients *coeff, float *t0, float *t1)
{
	float discriminant;
	float sqrt_disc;
	float tmp;

	discriminant = coeff->b * coeff->b - 4 * coeff->a * coeff->c;
	if (discriminant < 0.0f)
		return (false);
	sqrt_disc = sqrtf(discriminant);
	*t0 = (-coeff->b - sqrt_disc) / (2.0f * coeff->a);
	*t1 = (-coeff->b + sqrt_disc) / (2.0f * coeff->a);
	if (*t0 > *t1)
	{
		tmp = *t0;
		*t0 = *t1;
		*t1 = tmp;
	}
	return (true);
}

static bool	valid_cylinder_hit(t_ray *ray, t_object *object, t_hit *hit, float t, t_vector axis)
{
	t_cylinder	*cylinder;
	t_vector	p;
	t_vector	cp;
	t_vector	normal;
	float height_on_axis;

	cylinder = (t_cylinder *)object->object;
	if (t < 0.001f)
		return (false);
	p = v_add(*ray->position, v_scalar_product(*ray->orientation, t));
	cp = v_sub(p, *cylinder->position);
	height_on_axis = v_dot_product(cp, axis);
	if (height_on_axis >= 0.0f && height_on_axis <= cylinder->height)
	{
		hit->t = t;
		hit->position = v_scalar_product(p, 1);
		normal = v_normalize(v_sub(cp, v_scalar_product(axis, height_on_axis)));
		hit->orientation = normal;
		hit->object = object;
		return (true);
	}
	return (false);
}

static bool	check_caps(t_ray *ray, t_object *object, t_hit *hit, t_vector axis)
{
	t_cylinder	*cylinder;
	int			i;

	cylinder = (t_cylinder *)object->object;
	t_vector	cap_centers[2] = {
		v_add(*cylinder->position, v_scalar_product(axis, 0.0f)),
		v_add(*cylinder->position, v_scalar_product(axis, cylinder->height))
	};
	i = 0;
	while (i < 2)
	{
		t_vector	cap_normal = (i == 0) ? v_scalar_product(axis, -1.0f) : axis;
		float denom = v_dot_product(cap_normal, *ray->orientation);

		if (fabs(denom) < 1e-6)
			continue;

		t_vector ocap = v_sub(cap_centers[i], *ray->position);
		float t = v_dot_product(ocap, cap_normal) / denom;

		if (t > EPSILON)
		{
			t_vector p = v_add(*ray->position, v_scalar_product(*ray->orientation, t));
			if (v_length(v_sub(p, cap_centers[i])) <= cylinder->diameter / 2.0f)
			{
				hit->t = t;
				hit->position = v_scalar_product(p, 1);
				hit->orientation = v_scalar_product(cap_normal, 1);
				hit->object = object;
				return (true);
			}
		}
		i++;
	}
	return (false);
}

bool	intersect_cylinder(t_ray *ray, t_object *object, t_hit *hit)
{
	t_cylinder		*cylinder;
	t_coefficients	coeff;
	t_vector		axis;
	float			t0; 
	float			t1;

	cylinder = (t_cylinder *)object->object;
	axis = compute_quadratic_parts(ray, cylinder, &coeff);
	if (solve_quadratic(&coeff, &t0, &t1))
	{
		if (valid_cylinder_hit(ray, object, hit, t0, axis) ||
			valid_cylinder_hit(ray, object, hit, t1, axis))
			return (true);
	}
	if (check_caps(ray, object, hit, axis))
		return (true);
	return (false);
}

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
	bool		hit_found;
	float		radius_sq;
	t_vector	cap_center;
	t_vector	cap_normal;

	cylinder = (t_cylinder *)object->object;
	radius_sq = powf(cylinder->diameter / 2.0f, 2);
	hit_found = false;
	hit->t = INFINITY;
	i = -1;
	while (++i < 2)
	{
		cap_center = (i == 0) ? *cylinder->position : 
					v_add(*cylinder->position, v_scalar_product(axis, cylinder->height));
		cap_normal = (i == 0) ? v_scalar_product(axis, -1.0f) : axis;
		
		float denom = v_dot_product(cap_normal, *ray->orientation);
		if (fabs(denom) <= EPSILON)
			continue;
			
		t_vector oc = v_sub(cap_center, *ray->position);
		float t = v_dot_product(oc, cap_normal) / denom;
		
		if (t < EPSILON || t >= hit->t)
			continue;
			
		t_vector p = v_add(*ray->position, v_scalar_product(*ray->orientation, t));
		t_vector diff = v_sub(p, cap_center);
		float dist_sq = v_dot_product(diff, diff);
		
		if (dist_sq <= radius_sq)
		{
			hit->t = t;
			hit->position = p;
			hit->orientation = cap_normal;
			hit->object = object;
			hit_found = true;
		}
	}
	return (hit_found);
}

bool	intersect_cylinder(t_ray *ray, t_object *object, t_hit *hit)
{
	t_cylinder		*cylinder;
	t_coefficients	coeff;
	t_vector		axis;
	float			t0, t1;
	t_hit			side_hit, cap_hit;
	bool			side_ok = false, cap_ok = false;

	cylinder = (t_cylinder *)object->object;
	axis = compute_quadratic_parts(ray, cylinder, &coeff);
	if (solve_quadratic(&coeff, &t0, &t1))
	{
		side_ok = valid_cylinder_hit(ray, object, &side_hit, t0, axis) ||
				  valid_cylinder_hit(ray, object, &side_hit, t1, axis);
	}
	cap_ok = check_caps(ray, object, &cap_hit, axis);
	if (side_ok && (!cap_ok || side_hit.t < cap_hit.t))
	{
		*hit = side_hit;
		return true;
	}
	else if (cap_ok)
	{
		*hit = cap_hit;
		return true;
	}
	return false;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 18:33:28 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/04/28 19:52:51 by ysaroyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static void	compute_quadratic_parts(t_ray *ray, t_cylinder *cylinder, float *a, float *b, float *c, t_vector **axis)
{
	t_vector	*oc;
	t_vector	*oc_proj;
	t_vector	*d_proj;
	t_vector	*a_part;
	t_vector	*b_part;

	*axis = v_normalize(cylinder->orientation);
	oc_proj = v_scalar_product(*axis, v_dot_product(oc, *axis));
	d_proj = v_scalar_product(*axis, v_dot_product(ray->orientation, *axis));
	a_part = v_sub(ray->orientation, d_proj);
	b_part = v_sub(oc, oc_proj);
	oc = v_sub(ray->position, cylinder->position);
	*a = v_dot_product(a_part, a_part);
	*b = 2.0f * v_dot_product(a_part, b_part);
	*c = v_dot_product(b_part, b_part) - powf(cylinder->diameter / 2.0f, 2);
	free(oc);
	free(oc_proj);
	free(d_proj);
	free(a_part);
	free(b_part);
}

static bool	solve_quadratic(float a, float b, float c, float *t0, float *t1)
{
	float discriminant = b * b - 4 * a * c;

	if (discriminant < 0.0f)
		return (false);

	float sqrt_disc = sqrtf(discriminant);
	*t0 = (-b - sqrt_disc) / (2.0f * a);
	*t1 = (-b + sqrt_disc) / (2.0f * a);

	if (*t0 > *t1)
	{
		float tmp = *t0;
		*t0 = *t1;
		*t1 = tmp;
	}
	return (true);
}

static bool	valid_cylinder_hit(t_ray *ray, t_cylinder *cylinder, t_hit *hit, float t, t_vector *axis)
{
	if (t < 0.001f)
		return (false);

	t_vector	*p = v_add(ray->position, v_scalar_product(ray->orientation, t));
	t_vector	*cp = v_sub(p, cylinder->position);
	float height_on_axis = v_dot_product(cp, axis);

	if (height_on_axis >= 0.0f && height_on_axis <= cylinder->height)
	{
		hit->t = t;
		hit->position = v_scalar_product(p, 1);
		t_vector	*proj = v_scalar_product(axis, height_on_axis);
		t_vector	*normal = v_normalize(v_sub(cp, proj));
		hit->orientation = normal;
		hit->object = (t_object *)cylinder;
		free(p);
		free(cp);
		free(proj);
		return (true);
	}

	free(p);
	free(cp);
	return (false);
}

static bool	check_caps(t_ray *ray, t_cylinder *cylinder, t_hit *hit, t_vector *axis)
{
	t_vector	*cap_centers[2] = {
		v_add(cylinder->position, v_scalar_product(axis, 0.0f)),
		v_add(cylinder->position, v_scalar_product(axis, cylinder->height))
	};

	for (int i = 0; i < 2; i++)
	{
		t_vector	*cap_normal = (i == 0) ? v_scalar_product(axis, -1.0f) : axis;
		float denom = v_dot_product(cap_normal, ray->orientation);

		if (fabs(denom) < 1e-6)
			continue;

		t_vector *ocap = v_sub(cap_centers[i], ray->position);
		float t = v_dot_product(ocap, cap_normal) / denom;

		if (t > 0.001f)
		{
			t_vector *p = v_add(ray->position, v_scalar_product(ray->orientation, t));
			if (v_length(v_sub(p, cap_centers[i])) <= cylinder->diameter / 2.0f)
			{
				hit->t = t;
				hit->position = v_scalar_product(p, 1);
				hit->orientation = v_scalar_product(cap_normal, 1);
				hit->object = (t_object *)cylinder;
				free(ocap);
				free(p);
				return (true);
			}
			free(p);
		}
		free(ocap);
	}
	free(cap_centers[0]);
	free(cap_centers[1]);
	return (false);
}

bool	intersect_cylinder(t_ray *ray, t_object *object, t_hit *hit)
{
	t_cylinder	*cylinder = (t_cylinder *)object->object;
	float		a, b, c, t0, t1;
	t_vector	*axis;

	compute_quadratic_parts(ray, cylinder, &a, &b, &c, &axis);
	if (solve_quadratic(a, b, c, &t0, &t1))
	{
		if (valid_cylinder_hit(ray, cylinder, hit, t0, axis) ||
			valid_cylinder_hit(ray, cylinder, hit, t1, axis))
		{
			free(axis);
			return (true);
		}
	}
	if (check_caps(ray, cylinder, hit, axis))
	{
		free(axis);
		return (true);
	}
	free(axis);
	return (false);
}

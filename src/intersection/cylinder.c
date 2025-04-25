/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 18:33:28 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/04/24 18:50:28 by ysaroyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

bool	intersect_cylinder(t_ray *ray, t_object *object, t_hit *hit)
{
	t_cylinder	*cylinder;

	cylinder = (t_cylinder *)object->object;
	t_vector	*oc = v_sub(ray->position, cylinder->position);
	t_vector	*dir = ray->orientation;
	t_vector	*axis = v_normalize(cylinder->orientation);
	t_vector	*oc_proj = v_scalar_product(axis, v_dot_product(oc, axis));
	t_vector	*d_proj = v_scalar_product(axis, v_dot_product(dir, axis));

	t_vector	*a_part = v_sub(dir, d_proj);
	t_vector	*b_part = v_sub(oc, oc_proj);

	float a = v_dot_product(a_part, a_part);
	float b = 2.0f * v_dot_product(a_part, b_part);
	float c = v_dot_product(b_part, b_part) - powf(cylinder->diameter / 2.0f, 2);


	float discriminant = b * b - 4 * a * c;
	if (discriminant < 0.0f)
		return false;

	float sqrt_disc = sqrtf(discriminant);
	float t0 = (-b - sqrt_disc) / (2.0f * a);
	float t1 = (-b + sqrt_disc) / (2.0f * a);

	if (t0 > t1) { float tmp = t0; t0 = t1; t1 = tmp; }

	for (int i = 0; i < 2; i++) {
		float t = (i == 0) ? t0 : t1;
		if (t < 0.001f) continue;

		t_vector	*p = v_add(ray->position, v_scalar_product(ray->orientation, t));
		t_vector	*cp = v_sub(p, cylinder->position);
		float height_on_axis = v_dot_product(cp, axis);

		if (height_on_axis >= 0.0f && height_on_axis <= cylinder->height) {
			hit->t = t;
			hit->position = v_scalar_product(p, 1);

			t_vector	*proj = v_scalar_product(axis, height_on_axis);
			t_vector	*normal = v_sub(cp, proj);
			hit->orientation = v_normalize(normal);

			hit->object = object;
			return true;
		}
	}

	t_vector	cap_centers[2] = {
		*v_add(cylinder->position, v_scalar_product(axis, 0.0f)),
		*v_add(cylinder->position, v_scalar_product(axis, cylinder->height))
	};

	for (int i = 0; i < 2; i++) {
		t_vector *cap_normal = axis;
		if (i == 0) cap_normal = v_scalar_product(cap_normal, -1.0f);
		float denom = v_dot_product(cap_normal, ray->orientation);
		if (fabs(denom) < 1e-6) continue;

		t_vector *ocap = v_sub(cap_centers + i, ray->position);
		float t = v_dot_product(ocap, cap_normal) / denom;
		if (t < 0.001f) continue;

		t_vector	*p = v_add(ray->position, v_scalar_product(ray->orientation, t));
		if (v_length(v_sub(p, cap_centers + i)) <= cylinder->diameter / 2.0f)
		{
			hit->t = t;
			hit->position = v_scalar_product(p, 1);
			hit->orientation = v_scalar_product(cap_normal, 1);
			hit->object = object;
			return true;
		}
	}


	return false;
}

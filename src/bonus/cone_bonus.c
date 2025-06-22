/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 19:50:45 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/06/22 20:21:23 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static void	compute_quadratic_parts(t_ray *ray, t_cone *cone,
		t_coefficients *coeff)
{
	float		k;
	float		d_dot_v;
	float		co_dot_v;
	t_vector	d_proj;
	t_vector	co_proj;

	k = (cone->diameter / 2.0f) / cone->height;
	d_dot_v = v_dot_product(*ray->orientation,
			v_normalize(*cone->orientation));
	co_dot_v = v_dot_product(v_sub(*ray->position,
				*cone->position), v_normalize(*cone->orientation));
	d_proj = v_sub(*ray->orientation,
			v_scalar_product(v_normalize(*cone->orientation), d_dot_v));
	co_proj = v_sub(v_sub(*ray->position, *cone->position),
			v_scalar_product(v_normalize(*cone->orientation), co_dot_v));
	coeff->a = v_dot_product(d_proj, d_proj) - k * k * d_dot_v * d_dot_v;
	coeff->b = 2.0f * (v_dot_product(d_proj, co_proj)
			- k * k * d_dot_v * co_dot_v);
	coeff->c = v_dot_product(co_proj, co_proj) - k * k * co_dot_v * co_dot_v;
}

static float	intersect_cone_cap(t_ray *ray, t_cone *cone, t_vector normal)
{
	float		denom;
	float		t;
	float		radius;
	t_vector	cap_center;
	t_vector	d;

	cap_center = v_add(*cone->position, v_scalar_product(normal, cone->height));
	denom = v_dot_product(*ray->orientation, normal);
	if (fabs(denom) < EPSILON)
		return (-1.0f);
	t = v_dot_product(v_sub(cap_center, *ray->position), normal) / denom;
	if (t < EPSILON)
		return (-1.0f);
	d = v_sub(v_add(*ray->position, v_scalar_product(*ray->orientation, t)),
			cap_center);
	radius = cone->diameter / 2.0f;
	if (v_dot_product(d, d) <= radius * radius)
		return (t);
	return (-1.0f);
}

static float	get_t_side(t_ray *ray, t_cone *cone, t_cone_props *props)
{
	t_coefficients	coeff;
	float			t_side;
	float			discriminant;

	compute_quadratic_parts(ray, cone, &coeff);
	discriminant = calculate_discriminant(coeff.a, coeff.b, coeff.c);
	if (discriminant < 0.0f)
		return (false);
	props->roots = calculate_hit(discriminant, coeff.a, coeff.b);
	t_side = fminf(props->roots.t1, props->roots.t2);
	if (t_side < EPSILON)
		t_side = fmaxf(props->roots.t1, props->roots.t2);
	return (t_side);
}

static void	set_valid_hit(t_cone *cone, t_hit *hit,
		t_ray *ray, t_cone_props props)
{
	t_vector	normal;
	t_vector	tmp;
	t_vector	proj;
	float		m;
	float		slope;

	normal = v_normalize(*cone->orientation);
	if (!props.cap_ok || (props.side_ok && props.t_side < props.t_cap))
	{
		hit->t = props.t_side;
		hit->position = props.p_side;
		tmp = v_scalar_product(normal, v_dot_product(props.apex_to_p, normal));
		proj = v_sub(props.apex_to_p, tmp);
		m = sqrtf(proj.x * proj.x + proj.y * proj.y + proj.z * proj.z);
		slope = (cone->diameter / 2.0f) / cone->height;
		hit->orientation = v_normalize(v_sub(props.apex_to_p,
					v_scalar_product(normal, m / slope)));
	}
	else
	{
		hit->t = props.t_cap;
		hit->position = v_add(*ray->position,
				v_scalar_product(*ray->orientation, props.t_cap));
		hit->orientation = normal;
	}
}

bool	intersect_cone(t_ray *ray, t_object *object, t_hit *hit)
{
	t_cone			*cone;
	t_vector		normal;
	t_cone_props	props;
	float			h_proj;

	cone = (t_cone *)object->object;
	normal = v_normalize(*cone->orientation);
	props.t_side = get_t_side(ray, cone, &props);
	props.p_side = v_add(*ray->position,
			v_scalar_product(*ray->orientation, props.t_side));
	props.apex_to_p = v_sub(props.p_side, *cone->position);
	h_proj = v_dot_product(props.apex_to_p, normal);
	props.side_ok = props.t_side >= EPSILON && props.t_side < hit->t
		&& h_proj >= 0.0f && h_proj <= cone->height;
	props.t_cap = intersect_cone_cap(ray, cone, normal);
	props.cap_ok = props.t_cap >= EPSILON && props.t_cap < hit->t;
	if (!props.side_ok && !props.cap_ok)
		return (false);
	set_valid_hit(cone, hit, ray, props);
	if (props.roots.t1 < 0)
		hit->orientation = v_scalar_product(hit->orientation, -1.0f);
	hit->object = object;
	return (true);
}

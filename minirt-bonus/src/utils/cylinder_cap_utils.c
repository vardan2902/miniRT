/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_cap_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 16:57:53 by vapetros          #+#    #+#             */
/*   Updated: 2025/06/14 21:27:26 by ysaroyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static t_cylinder_cap	calculate_cap(int i, t_cylinder *cylinder,
		t_vector axis)
{
	t_cylinder_cap	cap;

	cap.center = *cylinder->position;
	if (i != 0)
		cap.center = v_add(*cylinder->position,
				v_scalar_product(axis, cylinder->height));
	cap.normal = axis;
	if (i == 0)
		cap.normal = v_scalar_product(axis, -1.0f);
	return (cap);
}

static void	set_cap_hit_point(t_hit *hit, t_check_cap_props	*props,
	t_object *object, t_vector normal)
{
	if (props->dist_sq <= props->radius_sq)
	{
		hit->t = props->t;
		hit->position = props->p;
		hit->orientation = normal;
		hit->object = object;
		props->hit_found = true;
	}
}

static bool	check_cap(t_check_cap_props *props, t_cylinder_cap *cap,
	t_ray *ray, t_hit *hit)
{
	float		denom;

	denom = v_dot_product(cap->normal, *ray->orientation);
	if (fabs(denom) <= EPSILON)
		return (false);
	props->oc = v_sub(cap->center, *ray->position);
	props->t = v_dot_product(props->oc, cap->normal) / denom;
	if (props->t < EPSILON || props->t >= hit->t)
		return (false);
	return (true);
}

bool	check_caps(t_ray *ray, t_object *object, t_hit *hit,
	t_vector axis)
{
	t_cylinder			*cylinder;
	t_check_cap_props	props;
	t_cylinder_cap		cap;
	int					i;

	cylinder = (t_cylinder *)object->object;
	props.radius_sq = powf(cylinder->diameter / 2.0f, 2);
	props.hit_found = false;
	hit->t = INFINITY;
	i = -1;
	while (++i < 2)
	{
		cap = calculate_cap(i, cylinder, axis);
		if (!check_cap(&props, &cap, ray, hit))
			continue ;
		props.p = v_add(*ray->position,
				v_scalar_product(*ray->orientation, props.t));
		props.diff = v_sub(props.p, cap.center);
		props.dist_sq = v_dot_product(props.diff, props.diff);
		set_cap_hit_point(hit, &props, object, cap.normal);
	}
	return (props.hit_found);
}

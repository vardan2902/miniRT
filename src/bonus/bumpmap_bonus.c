/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bumpmap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 16:34:54 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/06/22 17:48:19 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static t_vector	get_bumped_sphere_orient(t_hit *hit, t_sphere *sphere)
{
	t_map_props	props;
	t_vector	up;

	if (!sphere->bumpmap)
		return (hit->orientation);
	props.n = v_normalize(v_sub(hit->position, *sphere->position));
	props.u = (0.5f + atan2f(props.n.z, props.n.x) / (2.0f * M_PI)) * 3.0f;
	props.v = (0.5f - asinf(props.n.y) / M_PI) * 3.0f;
	props.color = get_color_from_bumpmap(sphere->bumpmap, props.u, props.v);
	get_sampled(&props);
	if (fabsf(props.n.y) < 0.99f)
		up = (t_vector){0, 1, 0};
	else
		up = (t_vector){1, 0, 0};
	props.tangent = v_normalize(v_cross_product(up, props.n));
	props.bitangent = v_normalize(v_cross_product(props.n, props.tangent));
	props.bumped = v_add(
			v_add(
				v_scalar_product(props.tangent, props.sampled.x),
				v_scalar_product(props.bitangent, props.sampled.y)),
			v_scalar_product(props.n, props.sampled.z));
	return (v_normalize(props.bumped));
}

static t_vector	get_bumped_plane_orient(t_hit *hit, t_plane *plane)
{
	t_map_props	props;
	t_vector	up;
	t_vector	local;

	if (!plane->bumpmap)
		return (hit->orientation);
	props.n = v_normalize(*plane->orientation);
	if (fabsf(props.n.y) < 0.99f)
		up = (t_vector){0, 1, 0};
	else
		up = (t_vector){1, 0, 0};
	props.tangent = v_normalize(v_cross_product(up, props.n));
	props.bitangent = v_normalize(v_cross_product(props.n, props.tangent));
	local = v_sub(hit->position, *plane->position);
	props.u = v_dot_product(local, props.tangent) * 0.1f;
	props.v = v_dot_product(local, props.bitangent) * 0.1f;
	props.u = props.u - floorf(props.u);
	props.v = props.v - floorf(props.v);
	props.color = get_color_from_bumpmap(plane->bumpmap, props.u, props.v);
	get_sampled(&props);
	props.bumped = v_add(
			v_add(v_scalar_product(props.tangent, props.sampled.x),
				v_scalar_product(props.bitangent, props.sampled.y)),
			v_scalar_product(props.n, props.sampled.z));
	return (v_normalize(props.bumped));
}

static t_vector	get_bumped_cylinder_orient(t_hit *hit, t_cylinder *cylinder)
{
	t_map_props	props;
	t_vector	axis;
	t_vector	hit_vec;
	t_vector	p;

	if (!cylinder->bumpmap)
		return (hit->orientation);
	props.n = hit->orientation;
	axis = v_normalize(*cylinder->orientation);
	props.tangent = v_normalize(v_cross_product(axis, (t_vector){0, 1, 0}));
	if (v_length(props.tangent) == 0)
		props.tangent = v_normalize(v_cross_product(axis, (t_vector){1, 0, 0}));
	props.bitangent = v_normalize(v_cross_product(props.n, props.tangent));
	hit_vec = v_sub(hit->position, *cylinder->position);
	p = v_sub(hit_vec, v_scalar_product(axis, v_dot_product(hit_vec, axis)));
	props.u = (0.5f + atan2f(p.z, p.x) / (2 * M_PI)) * 3.0f;
	props.v = (v_dot_product(hit_vec, axis) / cylinder->height) * 3.0f;
	if (props.u < 0)
		props.u += 1.0f;
	props.color = get_color_from_bumpmap(cylinder->bumpmap, props.u, props.v);
	get_sampled(&props);
	get_bumped(&props);
	return (v_normalize(props.bumped));
}

static t_vector	get_bumped_cone_orient(t_hit *hit, t_cone *cone)
{
	t_map_props	props;
	t_vector	axis;
	t_vector	hit_vec;
	t_vector	radial;
	float		height_proj;

	if (!cone->bumpmap)
		return (hit->orientation);
	props.n = hit->orientation;
	axis = v_normalize(*cone->orientation);
	props.tangent = v_normalize(v_cross_product(axis, (t_vector){0, 1, 0}));
	if (v_length(props.tangent) == 0)
		props.tangent = v_normalize(v_cross_product(axis, (t_vector){1, 0, 0}));
	props.bitangent = v_normalize(v_cross_product(props.n, props.tangent));
	hit_vec = v_sub(hit->position, *cone->position);
	height_proj = v_dot_product(hit_vec, axis);
	radial = v_sub(hit_vec, v_scalar_product(axis, height_proj));
	props.u = 0.5f + atan2f(radial.z, radial.x) / (2 * M_PI);
	if (props.u < 0)
		props.u += 1.0f;
	props.v = height_proj / cone->height;
	props.v = fminf(fmaxf(props.v, 0.0f), 1.0f);
	props.color = get_color_from_bumpmap(cone->bumpmap, props.u, props.v);
	get_sampled(&props);
	return (get_bumped(&props), v_normalize(props.bumped));
}

t_vector	get_bumped_orient(t_hit *hit)
{
	t_object	*object;

	object = (t_object *)hit->object;
	if (object->type == E_SPHERE)
		return (get_bumped_sphere_orient(hit, (t_sphere *)object->object));
	else if (object->type == E_PLANE)
		return (get_bumped_plane_orient(hit, (t_plane *)object->object));
	else if (object->type == E_CYLINDER)
		return (get_bumped_cylinder_orient(hit, (t_cylinder *)object->object));
	else if (object->type == E_CONE)
		return (get_bumped_cone_orient(hit, (t_cone *)object->object));
	else
		return ((t_vector){0, 0, 0});
}

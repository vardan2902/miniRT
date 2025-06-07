/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intensity.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:35:31 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/05/18 17:39:06 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static bool	is_in_shadow(t_scene *scene, t_hit *hit,
		t_vector light_dir, float distance)
{
	t_ray	shadow_ray;
	t_hit	shadow_hit;
	bool	hit_found;

	shadow_ray.position = (t_vector *)malloc(sizeof(t_vector));
	if (!shadow_ray.position)
		return (false);
	shadow_ray.orientation = (t_vector *)malloc(sizeof(t_vector));
	if (!shadow_ray.orientation)
		return (free(shadow_ray.position), false);
	assign_vector(hit->position, shadow_ray.position);
	assign_vector(light_dir, shadow_ray.orientation);
	shadow_hit.t = FLT_MAX;
	hit_found = find_hit(&shadow_ray, &shadow_hit, scene);
	free(shadow_ray.position);
	free(shadow_ray.orientation);
	return (hit_found && shadow_hit.t < distance);
}

static float	calculate_diffuse(t_vector *normal, t_vector light_dir)
{
	return (fmax(0.0f, v_dot_product(v_normalize(*normal), light_dir)));
}

static float	calculate_specular(t_vector normal, t_vector light_dir,
	t_vector view_dir)
{
	t_vector	reflection;
	float		spec_angle;
	float		shininess;

	shininess = 128.0f;
	reflection = v_reflect(v_scalar_product(light_dir, -1.0f), normal);
	spec_angle = fmax(0.0f, v_dot_product(v_normalize(reflection), view_dir));
	return (powf(spec_angle, shininess));
}

static float	calculate_attenuation(float distance)
{
	return (1.0f / (1.0f + 0.001f * distance));
}

t_light_effects	calculate_light_components(t_scene *scene, t_hit *hit, t_light *light)
{
	t_vector		light_dir;
	t_vector		view_dir;
	t_vector		normal;
	float			distance;
	t_light_effects	res;

	light_dir = v_sub(*light->position, hit->position);
	distance = v_length(light_dir);
	light_dir = v_normalize(light_dir);
	view_dir = v_normalize(v_sub(*scene->camera->position, hit->position));
	normal = v_normalize(hit->orientation);
	res.in_shadow = is_in_shadow(scene, hit, light_dir, distance);
	if (res.in_shadow)
		return (res);
	res.diffuse = calculate_diffuse(&normal, light_dir);
	res.specular = calculate_specular(normal, light_dir, view_dir);
	res.attenuation = calculate_attenuation(distance);
	return (res);
}

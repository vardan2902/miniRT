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

	shadow_ray.position = (t_vector *)malloc(sizeof (t_vector));
	if (!shadow_ray.position)
		return (false);
	shadow_ray.orientation = (t_vector *)malloc(sizeof (t_vector));
	if (!shadow_ray.orientation)
		return (free(shadow_ray.orientation), false);
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

static float	calculate_attenuation(float distance)
{
	return (1.0f / (1.0f + 0.001f * distance));
}

float	calculate_light_intensity(t_scene *scene, t_hit *hit)
{
	t_vector	light_dir;
	t_vector	normal;
	float		distance;
	float		diffuse;
	float		intensity;
	float		lighting;

	light_dir = v_sub(*scene->light->position, hit->position);
	distance = v_length(light_dir);
	normal = v_normalize(light_dir);
	if (scene->ambient)
		lighting = scene->ambient->lighting; 
	else
		lighting = 0.5f;
	if (is_in_shadow(scene, hit, normal, distance))
		return (lighting);
	diffuse = calculate_diffuse(&hit->orientation, normal);
	intensity = lighting + (scene->light->brightness * diffuse * calculate_attenuation(distance));
	return (fmin(1.0f, intensity));
}

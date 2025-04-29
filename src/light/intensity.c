/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intensity.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:35:31 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/04/26 20:32:47 by ysaroyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static bool	is_in_shadow(t_scene *scene, t_hit *hit,
		t_vector *light_dir, float distance)
{
	t_ray	shadow_ray;
	t_hit	shadow_hit;
	bool	hit_found;

	shadow_ray.position = hit->position;
	shadow_ray.orientation = light_dir;
	shadow_hit.t = FLT_MAX;
	shadow_hit.orientation = NULL;
	shadow_hit.position = NULL;
	hit_found = find_hit(&shadow_ray, &shadow_hit, scene);
	if (shadow_hit.position)
		free(shadow_hit.position);
	if (shadow_hit.orientation)
		free(shadow_hit.orientation);
	return (hit_found && shadow_hit.t < distance);
}

static float	calculate_diffuse(t_vector *normal, t_vector *light_dir)
{
	t_vector	*normalized;
	float		defuse;

	normalized = v_normalize(normal);
	defuse = fmax(0.0f, v_dot_product(normalized, light_dir));
	free(normalized);
	return (defuse);
}

static float	calculate_attenuation(float distance)
{
	return (1.0f / (1.0f + 0.001f * distance));
}

float	calculate_light_intensity(t_scene *scene, t_hit *hit)
{
	t_vector	*light_dir;
	t_vector	*normal;
	float		distance;
	float		diffuse;
	float		intensity;

	light_dir = v_sub(scene->light->position, hit->position);
	distance = v_length(light_dir);
	normal = v_normalize(light_dir);
	free(light_dir);
	if (is_in_shadow(scene, hit, normal, distance))
	{
		free(normal);
		return (scene->ambient->lighting);
	}
	diffuse = calculate_diffuse(hit->orientation, normal);
	free(normal);
	intensity = scene->ambient->lighting
		+ (scene->light->brightness * diffuse
			* calculate_attenuation(distance));
	return (fmin(1.0f, intensity));
}

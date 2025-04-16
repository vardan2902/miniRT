/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intensity.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:35:31 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/04/16 14:49:44 by ysaroyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static bool	is_in_shadow(t_scene *scene, t_hit hit,
		t_vector *light_dir, float distance)
{
	t_ray	shadow_ray;
	t_hit	shadow_hit;

	shadow_ray.position = hit.position;
	shadow_ray.orientation = light_dir;
	shadow_hit.t = FLT_MAX;
	return (
		find_hit(shadow_ray, &shadow_hit, scene)
		&& shadow_hit.t < distance
	);
}

static float	calculate_diffuse(t_vector *normal, t_vector *light_dir)
{
	return (fmax(0.0f, v_dot_product(v_normalize(normal), light_dir)));
}

static float	calculate_attenuation(float distance)
{
	return (1.0f / (1.0f + 0.001f * distance));
}

float	calculate_light_intensity(t_scene *scene, t_hit hit)
{
	t_vector	*light_dir;
	float		distance;
	float		diffuse;
	float		attenuation;
	float		intensity;

	light_dir = v_sub(scene->light->position, hit.position);
	distance = v_length(light_dir);
	light_dir = v_normalize(light_dir);
	if (is_in_shadow(scene, hit, light_dir, distance))
		return (scene->ambient->lighting);
	diffuse = calculate_diffuse(hit.orientation, light_dir);
	attenuation = calculate_attenuation(distance);
	intensity = scene->ambient->lighting
		+ (scene->light->brightness * diffuse * attenuation);
	return (fmin(1.0f, intensity));
}

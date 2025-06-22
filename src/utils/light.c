/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 16:58:05 by vapetros          #+#    #+#             */
/*   Updated: 2025/06/22 16:58:15 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

bool	is_in_shadow(t_scene *scene, t_hit *hit,
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
		return (free(shadow_ray.position), false);
	assign_vector(hit->position, shadow_ray.position);
	assign_vector(light_dir, shadow_ray.orientation);
	shadow_hit.t = FLT_MAX;
	hit_found = find_hit(&shadow_ray, &shadow_hit, scene);
	free(shadow_ray.position);
	free(shadow_ray.orientation);
	return (hit_found && shadow_hit.t < distance);
}

float	calculate_diffuse(t_vector *normal, t_vector light_dir)
{
	return (fmax(0.0f, v_dot_product(v_normalize(*normal), light_dir)));
}

float	calculate_attenuation(float distance)
{
	return (1.0f / (1.0f + 0.001f * distance));
}

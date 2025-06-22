/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intensity.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:35:31 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/06/22 16:59:21 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

float	calculate_light_intensity(t_scene *scene, t_hit *hit)
{
	t_vector	light_dir;
	t_vector	normal;
	float		distance;
	float		diffuse;
	float		intensity;

	light_dir = v_sub(*scene->light->position, hit->position);
	distance = v_length(light_dir);
	normal = v_normalize(light_dir);
	if (is_in_shadow(scene, hit, normal, distance))
		return (scene->ambient->lighting);
	diffuse = calculate_diffuse(&hit->orientation, normal);
	intensity = scene->ambient->lighting + (scene->light->brightness * diffuse
			* calculate_attenuation(distance));
	return (fmin(1.0f, intensity));
}

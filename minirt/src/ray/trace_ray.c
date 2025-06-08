/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 19:19:59 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/06/08 18:25:27 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static t_rgb	*get_rgb_by_type(t_object *object)
{
	if (object->type == E_SPHERE)
		return (((t_sphere *)object->object)->rgb);
	if (object->type == E_CYLINDER)
		return (((t_cylinder *)object->object)->rgb);
	if (object->type == E_PLANE)
		return (((t_plane *)object->object)->rgb);
	return (NULL);
}

static t_rgb	color_scale(t_rgb rgb, float intensity)
{
	return ((t_rgb){rgb.r * intensity, rgb.g * intensity, rgb.b * intensity});
}

t_rgb	trace_ray(t_ray *ray, t_scene *scene)
{
	t_hit	hit;
	t_rgb	*rgb;
	t_rgb	light_effect;
	t_rgb	ambient_effect;
	float	light_intensity;

	hit.t = FLT_MAX;
	if (!find_hit(ray, &hit, scene))
		return ((t_rgb){0.0, 0.0, 0.0});
	light_intensity = calculate_light_intensity(scene, &hit);
	rgb = get_rgb_by_type(hit.object);
	ambient_effect = color_scale(*scene->ambient->rgb,
			scene->ambient->lighting);
	light_effect = color_scale(*rgb, light_intensity);
	return ((t_rgb){
		fmin(255, ambient_effect.r + light_effect.r),
		fmin(255, ambient_effect.g + light_effect.g),
		fmin(255, ambient_effect.b + light_effect.b)
	});
}

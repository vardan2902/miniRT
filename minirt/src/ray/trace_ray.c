/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 19:19:59 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/06/14 19:48:53 by vapetros         ###   ########.fr       */
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

static t_rgb	calculate_final_color(t_rgb *ambient, t_rgb *light,
	t_object *active, t_object *hit)
{
	int	blur_effect;

	blur_effect = 0;
	if (active && active != hit)
		blur_effect = 100;
	return ((t_rgb){
		fmax(fmin(255, ambient->r + light->r + blur_effect), 0),
		fmax(fmin(255, ambient->g + light->g + blur_effect), 0),
		fmax(fmin(255, ambient->b + light->b + blur_effect), 0)
	});
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
	return (calculate_final_color(&ambient_effect, &light_effect,
			scene->mlx->hit_object, hit.object));
}

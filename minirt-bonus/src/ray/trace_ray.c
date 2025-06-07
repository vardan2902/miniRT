/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 19:19:59 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/05/18 17:41:13 by vapetros         ###   ########.fr       */
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
	if (object->type == E_CONE)
		return (((t_cone *)object->object)->rgb);
	return (NULL);
}

static t_rgb	get_ambient_effect(t_ambient *ambient, t_rgb obj_color)
{
	t_rgb	ambient_effect;

	if (ambient)
	{
		ambient_effect = (t_rgb){
			obj_color.r * ambient->rgb->r / 255.0f * ambient->lighting,
			obj_color.g * ambient->rgb->g / 255.0f * ambient->lighting,
			obj_color.b * ambient->rgb->b / 255.0f * ambient->lighting
		};
	}
	else
		ambient_effect = obj_color;
	return (ambient_effect);
}

t_rgb	trace_ray(t_ray *ray, t_scene *scene)
{
	t_hit			hit;
	t_rgb			obj_color;
	t_rgb			diffuse_effect = {0, 0, 0};
	t_rgb			specular_effect = {0, 0, 0};
	t_rgb			ambient_effect;
	t_rgb			final;
	t_light_effects	effects;

	hit.t = FLT_MAX;
	if (!find_hit(ray, &hit, scene))
		return ((t_rgb){0.0, 0.0, 0.0});	
	if (hit.object->checkerboard)
		obj_color = get_checker_color(hit.position, hit.object);
	else
		obj_color = *get_rgb_by_type(hit.object);
	hit.orientation = get_bumped_orient(&hit);
	ambient_effect = get_ambient_effect(scene->ambient, obj_color);
	t_list *light_node = scene->lights;
	while (light_node)
	{
		t_light *light = (t_light *)light_node->content;
		effects = calculate_light_components(scene, &hit, light);

		if (!effects.in_shadow)
		{
			diffuse_effect.r += obj_color.r * (light->rgb->r / 255.0f) * light->brightness * effects.diffuse * effects.attenuation;
			diffuse_effect.g += obj_color.g * (light->rgb->g / 255.0f) * light->brightness * effects.diffuse * effects.attenuation;
			diffuse_effect.b += obj_color.b * (light->rgb->b / 255.0f) * light->brightness * effects.diffuse * effects.attenuation;
			specular_effect.r += light->rgb->r * light->brightness * effects.specular * effects.attenuation;
			specular_effect.g += light->rgb->g * light->brightness * effects.specular * effects.attenuation;
			specular_effect.b += light->rgb->b * light->brightness * effects.specular * effects.attenuation;
		}
		light_node = light_node->next;
	}
	final = (t_rgb){
		fmin(255, ambient_effect.r + diffuse_effect.r + specular_effect.r),
		fmin(255, ambient_effect.g + diffuse_effect.g + specular_effect.g),
		fmin(255, ambient_effect.b + diffuse_effect.b + specular_effect.b)
	};
	return (final);
}

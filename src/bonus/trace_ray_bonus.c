/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_ray_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 17:47:10 by vapetros          #+#    #+#             */
/*   Updated: 2025/06/22 17:47:21 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

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

static t_rgb	calculate_final_color(t_rgb *ambient, t_rgb *diff_spec,
		t_object *active, t_object *hit)
{
	int	blur_effect;

	blur_effect = 0;
	if (active && active != hit)
		blur_effect = 100;
	return ((t_rgb){
		fmax(fmin(255, ambient->r + diff_spec->r + blur_effect), 0),
		fmax(fmin(255, ambient->g + diff_spec->g + blur_effect), 0),
		fmax(fmin(255, ambient->b + diff_spec->b + blur_effect), 0)
	});
}

static void	calculate_diffuse_and_specular(t_scene *scene,
		t_color_props color_props, t_rgb *diffuse, t_rgb *specular)
{
	t_list			*light_node;
	t_light_effects	effects;
	t_light			*light;

	light_node = scene->lights;
	while (light_node)
	{
		light = (t_light *)light_node->content;
		effects = calculate_light_components(scene, color_props.hit, light);
		if (!effects.in_shadow)
		{
			get_diffuse(effects, light, color_props.obj_color, diffuse);
			get_specular(effects, light, specular);
		}
		light_node = light_node->next;
	}
}

t_rgb	trace_ray(t_ray *ray, t_scene *scene)
{
	t_hit			hit;
	t_rgb			obj_color;
	t_rgb			diffuse;
	t_rgb			specular;
	t_rgb			ambient;

	hit.t = FLT_MAX;
	diffuse = (t_rgb){0, 0, 0};
	specular = (t_rgb){0, 0, 0};
	if (!find_hit(ray, &hit, scene))
		return ((t_rgb){0.0, 0.0, 0.0});
	if (hit.object->checkerboard)
		obj_color = get_checker_color(hit.position, hit.object);
	else
		obj_color = *get_rgb_by_type(hit.object);
	hit.orientation = get_bumped_orient(&hit);
	ambient = get_ambient_effect(scene->ambient, obj_color);
	calculate_diffuse_and_specular(scene, (t_color_props){&hit, &obj_color},
		&diffuse, &specular);
	return (calculate_final_color(&ambient, &(t_rgb){
			diffuse.r + specular.r,
			diffuse.g + specular.g,
			diffuse.b + specular.b
		}, scene->mlx->hit_object, hit.object));
}

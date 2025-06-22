/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 16:59:54 by vapetros          #+#    #+#             */
/*   Updated: 2025/06/22 17:00:44 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

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

t_light_effects	calculate_light_components(t_scene *scene, t_hit *hit,
		t_light *light)
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

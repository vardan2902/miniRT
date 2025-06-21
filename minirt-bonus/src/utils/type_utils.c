/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 14:49:09 by vapetros          #+#    #+#             */
/*   Updated: 2025/06/21 16:14:41 by ysaroyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_vector	*get_position_by_type(t_object *object)
{
	if (object->type == E_SPHERE)
		return (((t_sphere *)object->object)->position);
	if (object->type == E_CYLINDER)
		return (((t_cylinder *)object->object)->position);
	if (object->type == E_PLANE)
		return (((t_plane *)object->object)->position);
	if (object->type == E_CONE)
		return (((t_cone *)object->object)->position);
	return (NULL);
}

t_vector	*get_orientation_by_type(t_object *object)
{
	if (object->type == E_CYLINDER)
		return (((t_cylinder *)object->object)->orientation);
	if (object->type == E_PLANE)
		return (((t_plane *)object->object)->orientation);
	if (object->type == E_CONE)
		return (((t_cone *)object->object)->orientation);
	return (NULL);
}

void	get_diffuse(t_light_effects effects, t_light *light,
		t_rgb *obj_color, t_rgb *diffuse)
{
	diffuse->r += obj_color->r * (light->rgb->r / 255.0f)
		* light->brightness * effects.diffuse * effects.attenuation;
	diffuse->g += obj_color->g * (light->rgb->g / 255.0f)
		* light->brightness * effects.diffuse * effects.attenuation;
	diffuse->b += obj_color->b * (light->rgb->b / 255.0f)
		* light->brightness * effects.diffuse * effects.attenuation;
}

void	get_specular(t_light_effects effects, t_light *light, t_rgb *specular)
{
	specular->r += light->rgb->r * light->brightness
		* effects.specular * effects.attenuation;
	specular->g += light->rgb->g
		* light->brightness * effects.specular * effects.attenuation;
	specular->b += light->rgb->b * light->brightness
		* effects.specular * effects.attenuation;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 14:49:09 by vapetros          #+#    #+#             */
/*   Updated: 2025/06/07 14:49:20 by vapetros         ###   ########.fr       */
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
	return (NULL);
}

t_vector	*get_orientation_by_type(t_object *object)
{
	if (object->type == E_CYLINDER)
		return (((t_cylinder *)object->object)->orientation);
	if (object->type == E_PLANE)
		return (((t_plane *)object->object)->orientation);
	return (NULL);
}

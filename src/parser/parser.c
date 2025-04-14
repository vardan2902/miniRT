/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 20:43:58 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/04/14 17:20:35 by ysaroyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

bool	parse_line(t_scene *scene, char *id, char **line)
{
	if (!ft_strcmp(id, AMBIENT))
		return (parse_object((void **)&scene->ambient, line, id,
				build_ambient));
	if (!ft_strcmp(id, CAMERA))
		return (parse_object((void **)&scene->camera, line, id, build_camera));
	if (!ft_strcmp(id, LIGHT))
		return (parse_object((void **)&scene->light, line, id, build_light));
	if (!ft_strcmp(id, SPHERE))
		return (assign_object_list(&scene->object_list, E_SPHERE, line,
				build_sphere));
	if (!ft_strcmp(id, CYLINDER))
		return (assign_object_list(&scene->object_list, E_CYLINDER, line,
				build_cylinder));
	if (!ft_strcmp(id, PLANE))
		return (assign_object_list(&scene->object_list, E_PLANE, line,
				build_plane));
	return (false);
}

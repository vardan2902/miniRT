/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 20:40:21 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/06/22 17:36:29 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	*build_camera(char **line)
{
	t_camera	*camera;

	camera = NULL;
	if (!check_arg_count(line[3])
		|| !create_object((void **)&camera, sizeof (t_camera))
		|| !set_position(line[0], &camera->position)
		|| !set_orientation(line[1], &camera->orientation))
	{
		if (camera)
			cleanup_camera(camera);
		return (NULL);
	}
	if (!is_in_limit(line[2], DEG_MIN, DEG_MAX)
		|| !to_float(line[2], &camera->fov))
	{
		log_error(ERR_INVALID_TOKEN, line[2]);
		return (cleanup_camera(camera), NULL);
	}
	camera->up = (t_vector){0, 1, 0};
	if (camera->orientation->y > 0.9f)
		camera->up = (t_vector){0, 0, 1};
	else if (camera->orientation->y < -0.9f)
		camera->up = (t_vector){0, 0, 1};
	return (camera);
}

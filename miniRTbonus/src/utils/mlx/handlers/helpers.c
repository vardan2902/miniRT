/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 16:26:56 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/05/18 19:50:42 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>


t_vector rotate_vector_around_x(t_vector v, float angle)
{
	t_vector result;
	float cos_a = cosf(angle);
	float sin_a = sinf(angle);

	result.x = v.x;
	result.y = v.y * cos_a - v.z * sin_a;
	result.z = v.y * sin_a + v.z * cos_a;
	return result;
}

t_vector rotate_vector_around_y(t_vector v, float angle)
{
	t_vector result;
	float cos_a = cosf(angle);
	float sin_a = sinf(angle);

	result.x = v.x * cos_a + v.z * sin_a;
	result.y = v.y;
	result.z = -v.x * sin_a + v.z * cos_a;
	return result;
}

t_vector rotate_vector_around_z(t_vector v, float angle)
{
	t_vector result;
	float cos_a = cosf(angle);
	float sin_a = sinf(angle);

	result.x = v.x * cos_a - v.y * sin_a;
	result.y = v.x * sin_a + v.y * cos_a;
	result.z = v.z;
	return result;
}

void change_camera_orient(char axis, t_mlx *mlx, float angle) {
    t_camera *cam = mlx->scene->camera;
    t_vector *orient = cam->orientation;
    t_vector rotated_orient, rotated_up;

    if (axis == 'x') {
        rotated_orient = rotate_vector_around_x(*orient, angle);
        rotated_up = rotate_vector_around_x(cam->up, angle);
    } else if (axis == 'y') {
        rotated_orient = rotate_vector_around_y(*orient, angle);
        rotated_up = rotate_vector_around_y(cam->up, angle);
    } else if (axis == 'z') {
        rotated_orient = rotate_vector_around_z(*orient, angle);
        rotated_up = rotate_vector_around_z(cam->up, angle);
    } else return;

    *cam->orientation = v_normalize(rotated_orient);
    cam->up = v_normalize(rotated_up);
    mlx->need_render = true;
}
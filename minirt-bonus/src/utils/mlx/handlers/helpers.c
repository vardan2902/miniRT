/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 16:26:56 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/06/14 21:24:10 by ysaroyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_vector	rotate_vector_around_x(t_vector v, float angle)
{
	t_vector	result;
	float		cos_a;
	float		sin_a;

	cos_a = cosf(angle);
	sin_a = sinf(angle);
	result.x = v.x;
	result.y = v.y * cos_a - v.z * sin_a;
	result.z = v.y * sin_a + v.z * cos_a;
	return (result);
}

t_vector	rotate_vector_around_y(t_vector v, float angle)
{
	t_vector	result;
	float		cos_a;
	float		sin_a;

	cos_a = cosf(angle);
	sin_a = sinf(angle);
	result.x = v.x * cos_a + v.z * sin_a;
	result.y = v.y;
	result.z = -v.x * sin_a + v.z * cos_a;
	return (result);
}

t_vector	rotate_vector_around_z(t_vector v, float angle)
{
	t_vector	result;
	float		cos_a;
	float		sin_a;

	cos_a = cosf(angle);
	sin_a = sinf(angle);
	result.x = v.x * cos_a - v.y * sin_a;
	result.y = v.x * sin_a + v.y * cos_a;
	result.z = v.z;
	return (result);
}

void	change_camera_orient(char axis, t_mlx *mlx, float angle)
{
	t_camera	*cam;
	t_vector	*orient;
	t_vector	rotated_up;
	t_vector	rotated_orient;

	t_vector (*rotate[3])(t_vector, float);
	cam = mlx->scene->camera;
	orient = cam->orientation;
	rotate[0] = rotate_vector_around_x;
	rotate[1] = rotate_vector_around_y;
	rotate[2] = rotate_vector_around_z;
	if (!ft_strchr("xyz", axis))
		return ;
	rotated_orient = rotate[axis - 'x'](*orient, angle);
	rotated_up = rotate[axis - 'x'](cam->up, angle);
	*cam->orientation = v_normalize(rotated_orient);
	cam->up = v_normalize(rotated_up);
	mlx->need_render = true;
}

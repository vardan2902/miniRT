/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 17:56:52 by vapetros          #+#    #+#             */
/*   Updated: 2025/06/22 17:57:12 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

int	handle_close(void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)param;
	cleanup_scene(mlx->scene);
	if (mlx->img)
	{
		free(mlx->img->img->image);
		free(mlx->img->img);
		free(mlx->img);
	}
	mlx_destroy_window(mlx->ptr, mlx->win);
	if (mlx->ptr)
	{
		mlx_destroy_display(mlx->ptr);
		free(mlx->ptr);
	}
	exit(0);
}

void	handle_camera_rotate(int key, t_mlx *mlx)
{
	if (key == XK_w)
		change_camera_orient('x', mlx, -0.1f);
	else if (key == XK_s)
		change_camera_orient('x', mlx, 0.1f);
	else if (key == XK_a)
		change_camera_orient('y', mlx, -0.1f);
	else if (key == XK_d)
		change_camera_orient('y', mlx, 0.1f);
	else if (key == XK_q)
		change_camera_orient('z', mlx, -0.1f);
	else if (key == XK_e)
		change_camera_orient('z', mlx, 0.1f);
}

void	handle_transform_actions(int key, t_mlx *mlx)
{
	if (key == XK_0)
	{
		mlx->hit_object = NULL;
		mlx->need_render = true;
	}
	if (key == XK_r || key == XK_t)
		mlx->action = key;
	else if (key == XK_x || key == XK_y || key == XK_z)
		mlx->axis = key;
	else if (key == XK_Up || key == XK_Down)
	{
		if (!mlx->hit_object || !mlx->action || !mlx->axis)
			return ;
		if (mlx->action == XK_r)
			rotate_object(mlx, key);
		else if (mlx->action == XK_t)
			translate_object(mlx, key);
	}
}

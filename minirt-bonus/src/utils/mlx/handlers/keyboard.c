/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 18:55:22 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/05/18 19:22:25 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

int handle_close(void *param)
{
	t_mlx *mlx;

	mlx = (t_mlx *)param;
	cleanup_scene(mlx->scene);
	mlx_destroy_window(mlx->ptr, mlx->win);
	exit(0);
}

static void handle_camera_rotate(int key, t_mlx *mlx)
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

static void handle_checkerboard(t_mlx *mlx)
{
	t_list *obj;
	t_object *object;
	obj = mlx->scene->object_list;
	while (obj)
	{
		object = (t_object *)obj->content;
		object->checkerboard = !object->checkerboard;
		obj = obj->next;
	}
	mlx->need_render = true;
}

int handle_keypress(int key, void *param)
{
	t_mlx *mlx;

	mlx = (t_mlx *)param;
	if (key == XK_Escape)
		handle_close(param);
	if (key == XK_1)
		handle_checkerboard(mlx);
	handle_camera_rotate(key, mlx);
	return (0);
}

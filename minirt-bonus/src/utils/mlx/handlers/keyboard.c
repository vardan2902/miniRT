/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 18:55:22 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/06/21 15:43:50 by ysaroyan         ###   ########.fr       */
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

static void	handle_camera_rotate(int key, t_mlx *mlx)
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

static void	handle_checkerboard(t_mlx *mlx)
{
	t_list		*obj;
	t_object	*object;

	obj = mlx->scene->object_list;
	while (obj)
	{
		object = (t_object *)obj->content;
		object->checkerboard = !object->checkerboard;
		obj = obj->next;
	}
	mlx->need_render = true;
}

static void	handle_transform_actions(int key, t_mlx *mlx)
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

int	handle_keypress(int key, void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)param;
	if (key == XK_Escape)
		handle_close(param);
	if (key == XK_1)
		handle_checkerboard(mlx);
	handle_camera_rotate(key, mlx);
	handle_transform_actions(key, mlx);
	return (0);
}

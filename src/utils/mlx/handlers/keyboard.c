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

int	handle_close(void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)param;
	cleanup_scene(mlx->scene);
	mlx_destroy_window(mlx->ptr, mlx->win);
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

static void	handle_light_translation(int key, t_mlx *mlx)
{
	if (key == XK_l)
		change_light_pos(&(t_vector){6.0f, 0, 0}, mlx);
	else if (key == XK_j)
		change_light_pos(&(t_vector){-6.0f, 0, 0}, mlx);
	else if (key == XK_i)
		change_light_pos(&(t_vector){0, 6.0f, 0}, mlx);
	else if (key == XK_k)
		change_light_pos(&(t_vector){0, -6.0f, 0}, mlx);
	else if (key == XK_o)
		change_light_pos(&(t_vector){0, 0, 6.0f}, mlx);
	else if (key == XK_u)
		change_light_pos(&(t_vector){0, 0, -6.0f}, mlx);
}

int	handle_keypress(int key, void *param)
{
	t_mlx		*mlx;

	mlx = (t_mlx *)param;
	if (key == XK_Escape)
		handle_close(param);
	handle_camera_rotate(key, mlx);
	if (mlx->scene->light)
		handle_light_translation(key, mlx);
	return (0);
}

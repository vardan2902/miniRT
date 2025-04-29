/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 18:55:22 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/04/26 16:57:10 by ysaroyan         ###   ########.fr       */
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
	t_vector	*right;
	t_vector	*right_scalar;

	right_scalar = v_cross_product(mlx->scene->camera->orientation,
			&(t_vector){0, 1.1f, 0});
	right = v_normalize(right_scalar);
	if (key == XK_w)
		change_camera_orient(right, mlx, -0.05f);
	else if (key == XK_s)
		change_camera_orient(right, mlx, 0.05f);
	else if (key == XK_a)
		change_camera_orient(&(t_vector){0, 1.1f, 0}, mlx, -0.05f);
	else if (key == XK_d)
		change_camera_orient(&(t_vector){0, 1.1f, 0}, mlx, 0.05f);
	else if (key == XK_q)
		change_camera_orient(mlx->scene->camera->orientation, mlx, -0.05f);
	else if (key == XK_e)
		change_camera_orient(mlx->scene->camera->orientation, mlx, 0.05f);
	free(right_scalar);
	free(right);
}

static void	handle_light_translation(int key, t_mlx *mlx)
{
	if (key == XK_l)
		change_light_pos(&(t_vector){0.2f, 0, 0}, mlx);
	else if (key == XK_j)
		change_light_pos(&(t_vector){-1.0f, 0, 0}, mlx);
	else if (key == XK_i)
		change_light_pos(&(t_vector){0, 1.0f, 0}, mlx);
	else if (key == XK_k)
		change_light_pos(&(t_vector){0, -1.0f, 0}, mlx);
	else if (key == XK_o)
		change_light_pos(&(t_vector){0, 0, 1.0f}, mlx);
	else if (key == XK_u)
		change_light_pos(&(t_vector){0, 0, -1.0f}, mlx);
}

int	handle_keypress(int key, void *param)
{
	t_mlx		*mlx;

	mlx = (t_mlx *)param;
	if (key == XK_Escape)
		handle_close(param);
	handle_camera_rotate(key, mlx);
	handle_light_translation(key, mlx);
	return (0);
}

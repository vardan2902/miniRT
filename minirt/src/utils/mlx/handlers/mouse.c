/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 18:54:47 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/06/08 17:43:54 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static void	save_current_pixel(t_mlx *mlx, int x, int y)
{
	mlx->mouse_state.last_x = x;
	mlx->mouse_state.last_y = y;
	mlx->need_render = true;
}

static int	handle_scroll(int button, int x, int y, t_mlx *mlx)
{
	if (button == SCROLL_UP)
	{
		if (!pick_object_at(x, y, mlx->scene, &mlx->mouse_state.hit_object)
			|| mlx->mouse_state.hit_object->type == E_PLANE)
			return (0);
		resize_object(mlx, true);
		save_current_pixel(mlx, x, y);
	}
	else if (button == SCROLL_DOWN)
	{
		if (!pick_object_at(x, y, mlx->scene, &mlx->mouse_state.hit_object)
			|| mlx->mouse_state.hit_object->type == E_PLANE)
			return (0);
		resize_object(mlx, false);
		save_current_pixel(mlx, x, y);
	}
	return (1);
}

int	handle_mouse_press(int button, int x, int y, void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)param;
	if (button == LEFT_CLICK)
	{
		if (!pick_object_at(x, y, mlx->scene, &mlx->mouse_state.hit_object))
			return (0);
		mlx->mouse_state.left_pressed = true;
		mlx->mouse_state.last_x = x;
		mlx->mouse_state.last_y = y;
	}
	else if (button == RIGHT_CLICK)
	{
		if (!pick_object_at(x, y, mlx->scene, &mlx->mouse_state.hit_object)
			|| mlx->mouse_state.hit_object->type == E_SPHERE)
			return (0);
		mlx->mouse_state.right_pressed = true;
		mlx->mouse_state.last_x = x;
		mlx->mouse_state.last_y = y;
	}
	if (!handle_scroll(button, x, y, mlx))
		return (0);
	return (0);
}

int	handle_mouse_release(int button, int x, int y, void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)param;
	(void)x;
	(void)y;
	if (button == LEFT_CLICK)
		mlx->mouse_state.left_pressed = false;
	if (button == RIGHT_CLICK)
		mlx->mouse_state.right_pressed = false;
	return (0);
}

int	handle_mouse_move(int x, int y, void *param)
{
	float		dx;
	float		dy;
	t_mlx		*mlx;

	mlx = (t_mlx *)param;
	if (!mlx->mouse_state.last_x || !mlx->mouse_state.last_y
		|| !mlx->mouse_state.hit_object)
		return (0);
	dx = x - mlx->mouse_state.last_x;
	dy = y - mlx->mouse_state.last_y;
	if (dx == 0 || dy == 0)
		return (0);
	if (mlx->mouse_state.left_pressed)
	{
		translate_object(mlx, dx, dy);
		save_current_pixel(mlx, x, y);
	}
	else if (mlx->mouse_state.right_pressed)
	{
		rotate_object(mlx, dx, dy);
		save_current_pixel(mlx, x, y);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:15:11 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/04/25 17:17:21 by ysaroyan         ###   ########.fr       */
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

int	handle_keypress(int key, void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)param;
	if (key == XK_Escape)
		handle_close(mlx);
	return (0);
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
	else if (button == SCROLL_UP)
	{
		if (!pick_object_at(x, y, mlx->scene, &mlx->mouse_state.hit_object)
			|| mlx->mouse_state.hit_object->type == E_PLANE)
			return (0);
		if (mlx->mouse_state.hit_object->type == E_SPHERE)
		{
			t_sphere	*sphere;

			sphere = (t_sphere *)mlx->mouse_state.hit_object->object;
			sphere->diameter += 1;
		}
		else if (mlx->mouse_state.hit_object->type == E_CYLINDER)
		{
			t_cylinder	*cylinder;

			cylinder = (t_cylinder *)mlx->mouse_state.hit_object->object;
			cylinder->diameter += 1;
			cylinder->height += 2;
		}
		mlx->mouse_state.last_x = x;
		mlx->mouse_state.last_y = y;
		mlx->need_render = true;
	}
	else if (button == SCROLL_DOWN)
	{
		if (!pick_object_at(x, y, mlx->scene, &mlx->mouse_state.hit_object)
			|| mlx->mouse_state.hit_object->type == E_PLANE)
			return (0);
		if (mlx->mouse_state.hit_object->type == E_SPHERE)
		{
			t_sphere	*sphere;

			sphere = (t_sphere *)mlx->mouse_state.hit_object->object;
			sphere->diameter -= 1;
		}
		else if (mlx->mouse_state.hit_object->type == E_CYLINDER)
		{
			t_cylinder	*cylinder;

			cylinder = (t_cylinder *)mlx->mouse_state.hit_object->object;
			cylinder->diameter -= 1;
			cylinder->height -= 2;
		}
		mlx->mouse_state.last_x = x;
		mlx->mouse_state.last_y = y;
		mlx->need_render = true;
	}
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

static t_vector *rotate_vector(t_vector *v, t_vector *axis, float angle)
{
	t_vector *normalized_axis = v_normalize(axis);
	float cos_theta = cosf(angle);
	float sin_theta = sinf(angle);

	t_vector *term1 = v_scalar_product(v, cos_theta);
	t_vector *term2 = v_scalar_product(v_cross_product(normalized_axis, v), sin_theta);
	t_vector *term3 = v_scalar_product(normalized_axis,
		v_dot_product(normalized_axis, v) * (1.0f - cos_theta));

	return v_add(v_add(term1, term2), term3);
}

int	handle_mouse_move(int x, int y, void *param)
{
	float		dx;
	float		dy;
	t_mlx		*mlx;
	t_vector	*position;
	t_vector	*orientation;

	mlx = (t_mlx *)param;
	dx = x - mlx->mouse_state.last_x;
	dy = y - mlx->mouse_state.last_y;
	if ((dx == 0 || dy == 0))
		return (0);
	if (mlx->mouse_state.left_pressed)
	{
		t_vector *forward = v_normalize(mlx->scene->camera->orientation);
		t_vector world_up = {0, 1, 0};
		t_vector *right = v_normalize(v_cross_product(forward, &world_up));
		t_vector *up = v_normalize(v_cross_product(right, forward));

		t_vector *new_pos;

		position = get_position_by_type(mlx->mouse_state.hit_object);
		new_pos = v_add(position, v_scalar_product(right, -dx * 0.03f));
		new_pos = v_add(new_pos, v_scalar_product(up, -dy * 0.03f));
		*position = *new_pos;
		mlx->mouse_state.last_x = x;
		mlx->mouse_state.last_y = y;
		mlx->need_render = true;
	}
	else if (mlx->mouse_state.right_pressed)
	{

		t_vector *forward = v_normalize(mlx->scene->camera->orientation);
		t_vector world_up = {0, 1, 0};
		t_vector *right = v_normalize(v_cross_product(forward, &world_up));
		t_vector *up = v_normalize(v_cross_product(right, forward));
		orientation = get_orientation_by_type(mlx->mouse_state.hit_object);
		if (dx != 0)
			*orientation = *rotate_vector(orientation, up, dx * 0.01f);
		if (dy != 0)
			*orientation = *rotate_vector(orientation, right, dy * 0.01f);
		*orientation = *v_normalize(orientation);
		mlx->mouse_state.last_x = x;
		mlx->mouse_state.last_y = y;
		mlx->need_render = true;
	}
	return (0);
}

// int

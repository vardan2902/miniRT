/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 19:29:15 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/04/26 19:29:34 by ysaroyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	resize_object(t_mlx *mlx, bool is_plus)
{
	t_sphere	*sphere;
	t_cylinder	*cylinder;

	if (mlx->mouse_state.hit_object->type == E_SPHERE)
	{
		sphere = (t_sphere *)mlx->mouse_state.hit_object->object;
		if (is_plus)
			sphere->diameter += 1;
		else
			sphere->diameter -= 1;
	}
	else if (mlx->mouse_state.hit_object->type == E_CYLINDER)
	{
		cylinder = (t_cylinder *)mlx->mouse_state.hit_object->object;
		if (is_plus)
		{
			cylinder->diameter += 1;
			cylinder->height += 2;
			return ;
		}
		cylinder->diameter -= 1;
		cylinder->height -= 2;
	}
}

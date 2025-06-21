/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 19:22:56 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/06/14 19:29:11 by ysaroyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	resize_cone_height(t_cone *cone, float delta)
{
	float	new_height;
	float	min_height;
	float	max_height;

	new_height = cone->height + delta * 2;
	min_height = fmin(MIN_HEIGHT, cone->initial_height);
	max_height = fmax(MAX_HEIGHT, cone->initial_height);
	if (new_height >= min_height && new_height <= max_height)
		cone->height = new_height;
	else if (new_height < min_height)
		cone->height = min_height;
	else if (new_height > max_height)
		cone->height = max_height;
}

void	resize_cone_diameter(t_cone *cone, float delta)
{
	float	new_diameter;
	float	min_diameter;
	float	max_diameter;

	new_diameter = cone->diameter + delta;
	min_diameter = fmin(MIN_DIAMETER, cone->initial_diameter);
	max_diameter = fmax(MAX_DIAMETER, cone->initial_diameter);
	if (new_diameter >= min_diameter && new_diameter <= max_diameter)
		cone->diameter = new_diameter;
	else if (new_diameter < min_diameter)
		cone->diameter = min_diameter;
	else if (new_diameter > max_diameter)
		cone->diameter = max_diameter;
}

void	resize_cylinder_height(t_cylinder *cylinder, float delta)
{
	float	new_height;
	float	min_height;
	float	max_height;

	new_height = cylinder->height + delta * 2;
	min_height = fmin(MIN_HEIGHT, cylinder->initial_height);
	max_height = fmax(MAX_HEIGHT, cylinder->initial_height);
	if (new_height >= min_height && new_height <= max_height)
		cylinder->height = new_height;
	else if (new_height < min_height)
		cylinder->height = min_height;
	else if (new_height > max_height)
		cylinder->height = max_height;
}

void	resize_cylinder_diameter(t_cylinder *cylinder, float delta)
{
	float	new_diameter;
	float	min_diameter;
	float	max_diameter;

	new_diameter = cylinder->diameter + delta;
	min_diameter = fmin(MIN_DIAMETER, cylinder->initial_diameter);
	max_diameter = fmax(MAX_DIAMETER, cylinder->initial_diameter);
	if (new_diameter >= min_diameter && new_diameter <= max_diameter)
		cylinder->diameter = new_diameter;
	else if (new_diameter < min_diameter)
		cylinder->diameter = min_diameter;
	else if (new_diameter > max_diameter)
		cylinder->diameter = max_diameter;
}

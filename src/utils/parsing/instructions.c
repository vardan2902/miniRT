/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:33:03 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/04/12 20:51:45 by ysaroyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

bool	set_vector(char **instuction, t_vector *vector)
{
	return (!(!to_float(instuction[0], &vector->x)
			|| !to_float(instuction[1], &vector->y)
			|| !to_float(instuction[2], &vector->z)));
}

bool	set_ratio(char *str, double *ratio, void *ptr)
{
	if (!is_in_limit(str, RATIO_MIN, RATIO_MAX)
		|| !to_float(str, ratio))
	{
		free_and_log(ptr, ERR_INVALID_TOKEN, str, NULL);
		return (false);
	}
	return (true);
}

bool	set_position(char *str, t_vector *pos, void *ptr)
{
	char	**position;

	position = ft_split(str, ',');
	if (!position)
	{
		free_and_perror(ptr, ERR_MALLOC, NULL);
		return (false);
	}
	if (!is_instruction_in_range(position, -DBL_MAX, DBL_MAX, 3)
		|| !set_vector(position, pos))
	{
		free_and_log(ptr, ERR_INVALID_TOKEN, str, position);
		return (false);
	}
	free_splitted(position);
	return (true);
}

bool	set_orientation(char *str, t_vector *orient, void *ptr)
{
	char	**orientation;

	orientation = ft_split(str, ',');
	if (!orientation)
	{
		free_and_perror(ptr, ERR_MALLOC, NULL);
		return (false);
	}
	if (!is_instruction_in_range(orientation, ORIENT_MIN, ORIENT_MAX, 3)
		|| !set_vector(orientation, orient))
	{
		free_and_log(ptr, ERR_INVALID_TOKEN, str, NULL);
		free_splitted(orientation);
		return (false);
	}
	free_splitted(orientation);
	return (true);
}

bool	set_rgb(char *str, t_rgb *color, void *ptr)
{
	char	**rgb;

	rgb = ft_split(str, ',');
	if (!check_rgb(rgb, str, ptr))
		return (false);
	assign_rgb(rgb, color);
	free_splitted(rgb);
	return (true);
}

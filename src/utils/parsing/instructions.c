/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:33:03 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/05/18 13:32:12 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

bool	set_vector(char **instuction, t_vector *v, bool is_orientation)
{
	t_vector	new_vec;

	if ((!to_float(instuction[0], &new_vec.x)
			|| !to_float(instuction[1], &new_vec.y)
			|| !to_float(instuction[2], &new_vec.z)))
		return (free(v), false);
	if (is_orientation)
		new_vec = v_normalize(new_vec);
	assign_vector(new_vec, v);
	return (true);
}

bool	set_ratio(char *str, float *ratio)
{
	if (!is_in_limit(str, RATIO_MIN, RATIO_MAX)
		|| !to_float(str, ratio))
	{
		log_error(ERR_INVALID_TOKEN, str);
		return (false);
	}
	return (true);
}

bool	set_position(char *str, t_vector **pos)
{
	char		**position;

	*pos = (t_vector *)malloc(sizeof (t_vector));
	if (!*pos)
		return (false);
	position = ft_split(str, ',');
	if (!position)
	{
		perror(ERR_MALLOC);
		free(*pos);
		return (false);
	}
	if (!is_instruction_in_range(position, -FLT_MAX, FLT_MAX, 3)
		|| !set_vector(position, *pos, false))
	{
		log_error(ERR_INVALID_TOKEN, str);
		free_splitted(position);
		free(*pos);
		return (false);
	}
	free_splitted(position);
	return (true);
}

bool	set_orientation(char *str, t_vector **orient)
{
	char	**orientation;

	*orient = (t_vector *)malloc(sizeof (t_vector));
	if (!*orient)
		return (false);
	orientation = ft_split(str, ',');
	if (!orientation)
	{
		perror(ERR_MALLOC);
		free(*orient);
		return (false);
	}
	if (!is_instruction_in_range(orientation, ORIENT_MIN, ORIENT_MAX, 3)
		|| !set_vector(orientation, *orient, true))
	{
		log_error(ERR_INVALID_TOKEN, str);
		free_splitted(orientation);
		free(*orient);
		return (false);
	}
	free_splitted(orientation);
	return (true);
}

bool	set_rgb(char *str, t_rgb **color)
{
	char	**rgb;
	t_rgb	*new_color;

	new_color = (t_rgb *)malloc(sizeof (t_rgb));
	if (!new_color)
		return (false);
	rgb = ft_split(str, ',');
	if (!check_rgb(rgb, str))
		return (false);
	assign_rgb(rgb, new_color);
	*color = new_color;
	free_splitted(rgb);
	return (true);
}

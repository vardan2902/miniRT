/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 20:43:06 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/04/12 20:43:28 by ysaroyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	*build_cylinder(char **line)
{
	t_cylinder	*cylinder;

	if (!check_arg_count(line[5])
		|| !create_object((void **)&cylinder, sizeof (t_cylinder))
		|| !set_position(line[0], &cylinder->position, cylinder)
		|| !set_orientation(line[1], &cylinder->orientation, cylinder))
		return (NULL);
	if (!is_in_limit(line[2], -DBL_MAX, DBL_MAX)
		|| !to_float(line[2], &cylinder->diameter))
	{
		free_and_log(cylinder, ERR_INVALID_TOKEN, line[2], NULL);
		return (NULL);
	}
	if (!is_in_limit(line[3], -DBL_MAX, DBL_MAX)
		|| !to_float(line[3], &cylinder->height))
	{
		free_and_log(cylinder, ERR_INVALID_TOKEN, line[3], NULL);
		return (NULL);
	}
	if (!set_rgb(line[4], &cylinder->rgb, cylinder))
		return (NULL);
	return (cylinder);
}

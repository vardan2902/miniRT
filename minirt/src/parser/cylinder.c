/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 20:43:06 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/06/21 20:49:25 by ysaroyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	*build_cylinder(char **line)
{
	t_cylinder	*cylinder;

	cylinder = NULL;
	if (!check_arg_count(line[5])
		|| !create_object((void **)&cylinder, sizeof (t_cylinder))
		|| !set_position(line[0], &cylinder->position)
		|| !set_orientation(line[1], &cylinder->orientation)
		|| !set_prop(line[2], &cylinder->diameter)
		|| !set_prop(line[3], &cylinder->height)
		|| !set_prop(line[2], &cylinder->initial_diameter)
		|| !set_prop(line[3], &cylinder->initial_height)
		|| !set_rgb(line[4], &cylinder->rgb))
	{
		if (cylinder)
			del_cylinder(cylinder);
		return (NULL);
	}
	return (cylinder);
}

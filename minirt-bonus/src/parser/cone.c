/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 20:49:59 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/06/14 20:51:41 by ysaroyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	*build_cone(t_mlx *mlx, char **line)
{
	t_cone	*cone;
	bool	has_bumpmap;
	char	*last_str;

	cone = NULL;
	if (!create_object((void **)&cone, sizeof (t_cone)))
		return (NULL);
	cone->bumpmap = NULL;
	has_bumpmap = false;
	last_str = line[5];
	if (line[5])
	{
		has_bumpmap = true;
		last_str = line[6];
	}
	if (!check_arg_count(last_str) || !set_position(line[0], &cone->position)
		|| !set_orientation(line[1], &cone->orientation)
		|| !set_prop(line[2], &cone->diameter)
		|| !set_prop(line[3], &cone->height)
		|| !set_prop(line[2], &cone->initial_diameter)
		|| !set_prop(line[3], &cone->initial_height)
		|| !set_rgb(line[4], &cone->rgb)
		|| (has_bumpmap && !set_bumpmap(mlx, line[5], &cone->bumpmap)))
		return (NULL);
	return (cone);
}

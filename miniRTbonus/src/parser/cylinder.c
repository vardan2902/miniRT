/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 20:43:06 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/04/14 17:53:11 by ysaroyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	*build_cylinder(t_mlx *mlx, char **line)
{
	t_cylinder	*cylinder;
	bool	has_bumpmap;
	char	*last_str;

	cylinder = NULL;
	if (!create_object((void **)&cylinder, sizeof (t_cylinder)))
		return (NULL);
	cylinder->bumpmap = NULL;
	has_bumpmap = false;
	last_str = line[5];
	if (line[5])
	{
		has_bumpmap = true;
		last_str = line[6];
	}
	if (!check_arg_count(last_str)
		|| !set_position(line[0], &cylinder->position)
		|| !set_orientation(line[1], &cylinder->orientation)
		|| !set_prop(line[2], &cylinder->diameter)
		|| !set_prop(line[3], &cylinder->height)
		|| !set_prop(line[2], &cylinder->initial_diameter)
		|| !set_prop(line[3], &cylinder->initial_height)
		|| !set_rgb(line[4], &cylinder->rgb)
		|| (has_bumpmap && !set_bumpmap(mlx, line[5], &cylinder->bumpmap)))
	{
		return (NULL);
	}
	return (cylinder);
}

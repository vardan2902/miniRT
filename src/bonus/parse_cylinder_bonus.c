/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 17:37:56 by vapetros          #+#    #+#             */
/*   Updated: 2025/06/22 17:38:52 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	*build_cylinder(t_mlx *mlx, char **line)
{
	t_cylinder	*cy;
	bool		has_bumpmap;
	char		*last_str;

	cy = NULL;
	if (!create_object((void **)&cy, sizeof (t_cylinder)))
		return (NULL);
	cy->bumpmap = NULL;
	has_bumpmap = false;
	last_str = line[5];
	if (line[5])
	{
		has_bumpmap = true;
		last_str = line[6];
	}
	if (!check_arg_count(last_str) || !set_position(line[0], &cy->position)
		|| !set_orientation(line[1], &cy->orientation)
		|| !set_prop(line[2], &cy->diameter)
		|| !set_prop(line[3], &cy->height)
		|| !set_prop(line[2], &cy->initial_diameter)
		|| !set_prop(line[3], &cy->initial_height)
		|| !set_rgb(line[4], &cy->rgb)
		|| (has_bumpmap && !set_bumpmap(mlx, line[5], &cy->bumpmap)))
		return (del_cylinder(cy), NULL);
	return (cy);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 17:42:56 by vapetros          #+#    #+#             */
/*   Updated: 2025/06/22 17:43:13 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	*build_plane(t_mlx *mlx, char **line)
{
	t_plane	*plane;
	bool	has_bumpmap;
	char	*last_str;

	plane = NULL;
	if (!create_object((void **)&plane, sizeof (t_plane)))
		return (NULL);
	plane->bumpmap = NULL;
	has_bumpmap = false;
	last_str = line[3];
	if (line[3])
	{
		has_bumpmap = true;
		last_str = line[4];
	}
	if (!check_arg_count(last_str)
		|| !set_position(line[0], &plane->position)
		|| !set_orientation(line[1], &plane->orientation)
		|| !set_rgb(line[2], &plane->rgb)
		|| (has_bumpmap && !set_bumpmap(mlx, line[3], &plane->bumpmap)))
		return (del_plane(plane), NULL);
	return (plane);
}

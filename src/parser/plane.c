/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 20:42:12 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/04/13 18:29:04 by ysaroyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	*build_plane(char **line)
{
	t_plane	*plane;

	plane = NULL;
	if (!check_arg_count(line[3])
		|| !create_object((void **)&plane, sizeof (t_plane))
		|| !set_position(line[0], &plane->position)
		|| !set_orientation(line[1], &plane->orientation)
		|| !set_rgb(line[2], &plane->rgb))
	{
		del_plane(plane);
		return (NULL);
	}
	return (plane);
}

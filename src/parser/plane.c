/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 20:42:12 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/04/12 20:42:28 by ysaroyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	*build_plane(char **line)
{
	t_plane	*plane;

	if (!check_arg_count(line[3])
		|| !create_object((void **)&plane, sizeof (t_plane))
		|| !set_position(line[0], &plane->position, plane)
		|| !set_orientation(line[1], &plane->orientation, plane)
		|| !set_rgb(line[2], &plane->rgb, plane))
		return (NULL);
	return (plane);
}

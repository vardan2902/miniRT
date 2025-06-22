/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 17:41:02 by vapetros          #+#    #+#             */
/*   Updated: 2025/06/22 17:41:19 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	*build_light(char **line)
{
	t_light	*light;

	light = NULL;
	if (!check_arg_count(line[3])
		|| !create_object((void **)&light, sizeof (t_light))
		|| !set_position(line[0], &light->position)
		|| !set_ratio(line[1], &light->brightness)
		|| !set_rgb(line[2], &light->rgb))
	{
		if (light)
			cleanup_light(light);
		return (NULL);
	}
	return (light);
}

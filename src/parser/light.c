/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 20:41:01 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/04/14 17:44:06 by ysaroyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	*build_light(char **line)
{
	t_light	*light;
	char	**rgb;

	light = NULL;
	if (!check_arg_count(line[3])
		|| !create_object((void **)&light, sizeof (t_light))
		|| !set_position(line[0], &light->position)
		|| !set_ratio(line[1], &light->brightness))
	{
		return (NULL);
	}
	rgb = ft_split(line[2], ',');
	if (!check_rgb(rgb, line[2]))
	{
		free_splitted(rgb);
		return (NULL);
	}
	free_splitted(rgb);
	return (light);
}

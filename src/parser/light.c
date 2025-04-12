/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 20:41:01 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/04/12 20:41:13 by ysaroyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	*build_light(char **line)
{
	t_light	*light;
	char	**rgb;

	if (!check_arg_count(line[3])
		|| !create_object((void **)&light, sizeof (t_light))
		|| !set_position(line[0], &light->position, light)
		|| !set_ratio(line[1], &light->brightness, light))
		return (NULL);
	rgb = ft_split(line[2], ',');
	if (!check_rgb(rgb, line[2], light))
	{
		free_splitted(rgb);
		return (NULL);
	}
	free_splitted(rgb);
	return (light);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 20:37:49 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/04/12 20:38:19 by ysaroyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	*build_ambient(char **line)
{
	t_ambient	*ambient;

	if (!check_arg_count(line[2])
		|| !create_object((void **)&ambient, sizeof (t_ambient))
		|| !set_ratio(line[0], &ambient->lighting, ambient)
		|| !set_rgb(line[1], &ambient->rgb, ambient))
		return (NULL);
	return (ambient);
}

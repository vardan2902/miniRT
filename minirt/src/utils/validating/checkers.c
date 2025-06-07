/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 19:56:36 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/04/13 20:25:16 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

bool	is_line_empty(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
		if (!ft_isspace(line[i]))
			return (false);
	return (true);
}

bool	is_identifier(char *str)
{
	return (!ft_strcmp(str, AMBIENT) || !ft_strcmp(str, CAMERA)
		|| !ft_strcmp(str, LIGHT) || !ft_strcmp(str, SPHERE)
		|| !ft_strcmp(str, CYLINDER) || !ft_strcmp(str, PLANE));
}

bool	is_instruction_in_range(char **inst, float min,
	float max, int size)
{
	int	i;

	i = -1;
	while (inst[++i])
		if (!is_in_limit(inst[i], min, max))
			return (false);
	return (i == size);
}

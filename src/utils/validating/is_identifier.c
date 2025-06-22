/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_identifier.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 18:19:14 by vapetros          #+#    #+#             */
/*   Updated: 2025/06/22 18:19:14 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

bool	is_identifier(char *str)
{
	return (!ft_strcmp(str, AMBIENT) || !ft_strcmp(str, CAMERA)
		|| !ft_strcmp(str, LIGHT) || !ft_strcmp(str, SPHERE)
		|| !ft_strcmp(str, CYLINDER) || !ft_strcmp(str, PLANE));
}

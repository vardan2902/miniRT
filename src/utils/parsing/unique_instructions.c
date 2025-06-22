/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unique_instructions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 18:54:15 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/05/18 13:18:45 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

bool	set_prop(char *str, float *prop)
{
	if (!is_in_limit(str, -FLT_MAX, FLT_MAX)
		|| !to_float(str, prop))
	{
		log_error(ERR_INVALID_TOKEN, str);
		return (false);
	}
	return (true);
}

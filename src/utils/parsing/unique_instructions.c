/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unique_instructions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 18:54:15 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/04/14 17:43:35 by ysaroyan         ###   ########.fr       */
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unique_instructions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 18:54:15 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/04/13 18:57:03 by ysaroyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

bool	set_prop(char *str, double *prop)
{
	if (!is_in_limit(str, -DBL_MAX, DBL_MAX)
		|| !to_float(str, prop))
	{
		log_error(ERR_INVALID_TOKEN, str);
		return (false);
	}
	return (true);
}

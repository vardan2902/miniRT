/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:39:45 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/04/11 20:42:36 by ysaroyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static bool	to_float(const char *str, double *fl)
{
	long double	result;
	double		decimal_factor;
	int			is_negative;
	int			decimal_point_seen;
	int			i;

	result = 0.0;
	decimal_factor = 0.1;
	is_negative = 0;
	decimal_point_seen = 0;
	i = 0;
	while (str[i] && ft_isspace(str[i]))
		++i;
	if (str[i] == '-')
	{
		is_negative = 1;
		++i;
	}
	while (str[i] && ft_isdigit(str[i]))
	{
		result = result * 10 + (str[i] - '0');
		++i;
	}
	if (str[i] == '.')
	{
		decimal_point_seen = 1;
		++i;
		while (str[i] && ft_isdigit(str[i]))
		{
			result += (str[i] - '0') * decimal_factor;
			decimal_factor /= 10;
			++i;
		}
	}
	while (str[i] && ft_isspace(str[i]))
		++i;
	if (str[i] != '\0')
		return (false);
	*fl = result;
	if (is_negative)
		*fl = -result;
	return (true);
}

bool	set_float(const char *str, double *out_value)
{
	double	result;

	if (!to_float(str, &result))
		return (false);
	if (out_value)
		*out_value = result;
	return (true);
}

bool	is_in_limit(const char *str, double min, double max)
{
	double	result;

	if (!to_float(str, &result))
		return (false);
	return (result >= min && result <= max);
}

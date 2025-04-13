/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:39:45 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/04/12 19:21:27 by ysaroyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static void	handle_integer(const char *str, int *i, long double *result,
	int *is_negative)
{
	while (str[*i] && ft_isspace(str[*i]))
		++(*i);
	if (str[*i] == '-')
	{
		*is_negative = 1;
		++(*i);
	}
	while (str[*i] && ft_isdigit(str[*i]))
	{
		*result = (*result) * 10 + (str[*i] - '0');
		++(*i);
	}
}

static void	handle_precision(const char *str, int *i, long double *result)
{
	double		decimal_factor;

	decimal_factor = 0.1;
	if (str[*i] == '.')
	{
		++(*i);
		while (str[*i] && ft_isdigit(str[*i]))
		{
			*result += (str[*i] - '0') * decimal_factor;
			decimal_factor /= 10;
			++(*i);
		}
	}
}

bool	to_float(const char *str, double *fl)
{
	long double	result;
	int			is_negative;
	int			i;

	result = 0.0;
	is_negative = 0;
	i = 0;
	handle_integer(str, &i, &result, &is_negative);
	handle_precision(str, &i, &result);
	while (str[i] && ft_isspace(str[i]))
		++i;
	if (str[i] != '\0')
		return (false);
	*fl = result;
	if (is_negative)
		*fl = -result;
	return (true);
}

bool	is_in_limit(const char *str, double min, double max)
{
	double	result;

	if (!to_float(str, &result))
		return (false);
	return (result >= min && result <= max);
}

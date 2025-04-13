/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_ops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 20:28:58 by vapetros          #+#    #+#             */
/*   Updated: 2025/04/13 20:29:07 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

float	v_length(t_vector *a)
{
	return (v_dot_product(a, a));
}

t_vector	*v_normilize(t_vector *a)
{
	return (v_scalar_product(a, 1.0f / v_length(a)));
}

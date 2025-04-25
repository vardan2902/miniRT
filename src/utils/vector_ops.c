/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_ops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 20:28:58 by vapetros          #+#    #+#             */
/*   Updated: 2025/04/24 18:41:34 by ysaroyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

float	v_length(t_vector *a)
{
	return (v_dot_product(a, a));
}

t_vector	*v_normalize(t_vector *a)
{
	return (v_scalar_product(a, 1.0f / v_length(a)));
}

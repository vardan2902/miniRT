/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 16:56:27 by vapetros          #+#    #+#             */
/*   Updated: 2025/05/18 13:05:59 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_vector	v_scalar_product(t_vector vec, float n)
{
	t_vector	new_vec;

	new_vec.x = vec.x * n;
	new_vec.y = vec.y * n;
	new_vec.z = vec.z * n;
	return (new_vec);
}

t_vector	v_add(t_vector a, t_vector b)
{
	t_vector	new_vec;

	new_vec.x = a.x + b.x;
	new_vec.y = a.y + b.y;
	new_vec.z = a.z + b.z;
	return (new_vec);
}

t_vector	v_sub(t_vector a, t_vector b)
{
	t_vector	new_vec;

	new_vec.x = a.x - b.x;
	new_vec.y = a.y - b.y;
	new_vec.z = a.z - b.z;
	return (new_vec);
}

float	v_dot_product(t_vector a, t_vector b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vector	v_cross_product(t_vector a, t_vector b)
{
	t_vector	new_vec;

	new_vec.x = a.y * b.z - a.z * b.y;
	new_vec.y = a.z * b.x - a.x * b.z;
	new_vec.z = a.x * b.y - a.y * b.x;
	return (new_vec);
}

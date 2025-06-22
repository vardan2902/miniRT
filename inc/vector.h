/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 20:29:47 by vapetros          #+#    #+#             */
/*   Updated: 2025/06/22 16:12:32 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include <minirt.h>

float		v_length(t_vector a);
float		v_dot_product(t_vector a, t_vector b);
t_vector	v_normalize(t_vector a);
t_vector	v_scalar_product(t_vector vec, float n);
t_vector	v_add(t_vector a, t_vector b);
t_vector	v_sub(t_vector a, t_vector b);
t_vector	v_cross_product(t_vector a, t_vector b);
void		assign_vector(t_vector src, t_vector *dst);
t_vector	v_rotate(t_vector v, t_vector axis, float angle);
t_vector	init_zero_vec(void);

#endif

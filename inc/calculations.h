/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculations.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:40:52 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/06/22 16:10:07 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CALCULATIONS_H
# define CALCULATIONS_H

# include <minirt.h>

void	calculate_coefficients(t_coefficients *coefficients,
			t_ray *ray, t_vector *position, float radius);
float	calculate_discriminant(float a, float b, float c);
t_roots	calculate_hit(float discriminant, float a, float b);

#endif

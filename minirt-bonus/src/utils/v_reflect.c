/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_reflect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 21:19:06 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/06/14 21:19:58 by ysaroyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_vector	v_reflect(t_vector inverted_light_dir, t_vector normal)
{
	return (v_sub(inverted_light_dir, v_scalar_product(normal, 2.0f
				* v_dot_product(normal, inverted_light_dir))));
}

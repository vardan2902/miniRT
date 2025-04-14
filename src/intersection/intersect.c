/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:36:08 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/04/14 15:09:14 by ysaroyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	intersect(t_object *object, t_ray ray, t_hit *hit)
{
	if (object->type == SPHERE)
		intersect_sphere(ray, object, hit);;
}

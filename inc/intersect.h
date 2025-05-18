/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:42:33 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/05/18 13:49:39 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECT_H
# define INTERSECT_H

# include <structs.h>

bool	intersect(t_object *object, t_ray *ray, t_hit *hit);
bool	intersect_sphere(t_ray *ray, t_object *sphere, t_hit *hit);
bool	intersect_plane(t_ray *ray, t_object *object, t_hit *hit);
// bool	intersect_cylinder(t_ray *ray, t_object *object, t_hit *hit);

#endif

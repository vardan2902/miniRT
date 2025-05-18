/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 20:38:30 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/05/18 13:59:17 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include <structs.h>

t_rgb	trace_ray(t_ray *ray, t_scene *scene);
void	generate_ray(t_ray *ray, t_camera *camera, int x, int y);

#endif

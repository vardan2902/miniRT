/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactions.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 19:40:05 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/06/22 16:44:08 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERACTIONS_H
# define INTERACTIONS_H

# include <minirt.h>

void	resize_sphere(t_object *hit_object, float delta);
void	resize_cylinder_height(t_cylinder *cylinder, float delta);
void	resize_cylinder_diameter(t_cylinder *cylinder, float delta);
void	resize_cylinder(t_object *hit_object, float delta);
void	resize_object(t_mlx *mlx, bool is_plus);
void	rotate_object(t_mlx *mlx, int key);
void	translate_object(t_mlx *mlx, int key);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_mandatory.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 19:34:00 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/06/22 19:52:12 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_MANDATORY_H
# define MINIRT_MANDATORY_H

# define LIGHT "L"

# include "defines.h"
# include "enums.h"
# include "structs.h"
# include "utils.h"
# include "vector.h"
# include "interactions.h"
# include "ray.h"
# include "light.h"
# include "calculations.h"
# include "intersect.h"
# include "handlers.h"
# include "parser.h"

void	change_light_pos(t_vector *change_vec, t_mlx *mlx);
void	handle_light_translation(int key, t_mlx *mlx);
void	*build_sphere(char **line);
void	*build_plane(char **line);
void	*build_cylinder(char **line);
bool	assign_object_list(t_list **list, enum e_object_types type,
			char **line, void *(build)(char **));
void	cleanup_light(t_light *light);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 15:29:31 by vapetros          #+#    #+#             */
/*   Updated: 2025/06/22 19:52:42 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_BONUS_H
# define MINIRT_BONUS_H

# define LIGHT "l"
# define CONE "co"
# define BUMPMAP "bumpmap"
# define ERR_MAP "miniRT: bump map file error: "

# include "defines.h"
# include "enums_bonus.h"
# include "structs_bonus.h"
# include "utils.h"
# include "vector.h"
# include "interactions.h"
# include "ray.h"
# include "calculations.h"
# include "intersect.h"
# include "handlers.h"
# include "parser.h"

bool			intersect_cone(t_ray *ray, t_object *object, t_hit *hit);
t_light_effects	calculate_light_components(t_scene *scene, t_hit *hit,
					t_light *light);
void			*build_sphere(t_mlx *mlx, char **line);
void			*build_plane(t_mlx *mlx, char **line);
void			*build_cylinder(t_mlx *mlx, char **line);
void			*build_cone(t_mlx *mlx, char **line);
t_vector		get_bumped_orient(t_hit *hit);
t_rgb			get_checker_color(t_vector point, t_object *object);
bool			assign_object_list(t_scene *scene, enum e_object_types type,
					char **line, void *(build)(t_mlx *, char **));
bool			assign_light_list(t_scene *scene, char **line,
					void *(build)(char **));
void			cleanup_light(void *content);
void			del_cone(void	*content);
bool			set_bumpmap(t_mlx *mlx, char *line, t_bumpmap **bumpmap);
float			get_bump_height(t_bumpmap *bumpmap, float u, float v);
t_rgb			get_color_from_bumpmap(t_bumpmap *bumpmap, float u, float v);
void			get_bumped(t_map_props *props);
void			get_sampled(t_map_props *props);
void			resize_cone_height(t_cone *cone, float delta);
void			resize_cone_diameter(t_cone *cone, float delta);
void			resize_cylinder_height(t_cylinder *cylinder, float delta);
void			resize_cylinder_diameter(t_cylinder *cylinder, float delta);
void			get_diffuse(t_light_effects effects, t_light *light,
					t_rgb *obj_color, t_rgb *diffuse);
void			get_specular(t_light_effects effects,
					t_light *light, t_rgb *specular);
t_vector		v_reflect(t_vector inverted_light_dir, t_vector normal);

#endif

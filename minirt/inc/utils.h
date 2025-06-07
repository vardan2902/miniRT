/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 20:05:35 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/06/07 17:16:45 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <minirt.h>
# include <handlers.h>
# include <parser.h>

int				validate_args(int argc, char **argv);
void			throw_error(char *msg);
void			log_error(char *msg, char *arg);
void			init_mlx(t_mlx *mlx);
void			register_hooks(t_mlx *mlx);
bool			is_line_empty(char *line);
bool			is_identifier(char *str);
bool			to_float(const char *str, float *out_value);
bool			is_in_limit(const char *str, float min, float max);
bool			is_instruction_in_range(char **inst, float min, float max,
					int size);
void			free_splitted(char **splitted);
void			init_scene(t_scene *scene);
void			cleanup_scene(t_scene *scene);
bool			set_vector(char **instuction, t_vector *v, bool is_orientation);
bool			set_ratio(char *str, float *ratio);
bool			set_position(char *str, t_vector **pos);
bool			set_orientation(char *str, t_vector **orient);
bool			set_rgb(char *str, t_rgb **color);
bool			set_prop(char *str, float *prop);
void			assign_rgb(char **instuction, t_rgb *rgb);
bool			create_object(void **obj, size_t size);
bool			check_rgb(char **rgb, char *str);
bool			check_arg_count(char *str);
bool			assign_object_list(t_list **list, enum e_object_types type,
					char **line, void *(build)(char **));
void			cleanup_camera(t_camera *camera);
void			cleanup_ambient(t_ambient *ambient);
void			cleanup_light(t_light *light);
void			del_sphere(void *content);
void			del_plane(void *content);
void			del_cylinder(void *content);
void			del_object(void	*content);
void			set_hit_point(t_hit *hit, float t, t_ray *ray,
					t_object *object);
bool			find_hit(t_ray *ray, t_hit *hit, t_scene *scene);
t_vector		*get_position_by_type(t_object *object);
t_vector		*get_orientation_by_type(t_object *object);
bool			pick_object_at(int x, int y, t_scene *scene, t_object **object);
void			free_ray(t_ray *ray);
t_vector		get_cam_right(t_mlx *mlx);
t_vector		get_cam_up(t_mlx *mlx, t_vector right);
t_basis			*get_camera_basis(t_camera *camera);
t_viewport		compute_viewport_size(float fov);
t_ndc			get_pixel_ndc(int x, int y);
void			set_cap_hit_point(t_hit *hit, t_check_cap_props	*props,
					t_object *object, t_vector normal);
t_cylinder_cap	calculate_cap(int i, t_cylinder *cylinder,
					t_vector axis);
bool			check_caps(t_ray *ray, t_object *object, t_hit *hit,
					t_vector axis);

#endif

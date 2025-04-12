/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 20:05:35 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/04/12 21:00:50 by ysaroyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <minirt.h>
# include <handlers.h>
# include <parser.h>

int		validate_args(int argc, char **argv);
void	throw_error(char *msg);
void	log_error(char *msg, char *arg);
void	init_mlx(t_mlx *mlx);
void	register_hooks(t_mlx *mlx);
bool	is_line_empty(char *line);
bool	is_identifier(char *str);
bool	to_float(const char *str, double *out_value);
bool	is_in_limit(const char *str, double min, double max);
bool	is_instruction_in_range(char **inst, double min, double max, int size);
void	free_splitted(char **splitted);
void	free_and_log(void *obj, char *msg, char *token,
			char **instruction);
void	free_and_perror(void *obj, char *msg, char **instruction);
void	init_scene(t_scene *scene);
void	cleanup_scene(t_scene *scene);
bool	set_vector(char **instuction, t_vector *vector);
bool	set_ratio(char *str, double *ratio, void *ptr);
bool	set_position(char *str, t_vector *pos, void *ptr);
bool	set_orientation(char *str, t_vector *orient, void *ptr);
bool	set_rgb(char *str, t_rgb *color, void *ptr);
void	assign_rgb(char **instuction, t_rgb *rgb);
bool	create_object(void **obj, size_t size);
bool	check_rgb(char **rgb, char *str, void *ptr);
bool	check_arg_count(char *str);
bool	assign_object_list(t_list **list, char **line,
			void *(build)(char **));
bool	parse_object(void **obj, char **line, char *id, void *(build)(char **));

#endif

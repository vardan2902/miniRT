/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:12:40 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/06/14 19:17:20 by ysaroyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

bool	parse_line(t_scene *scene, char *identifier, char **line);
void	parse_scene(t_scene *scene, int fd);
bool	parse_object(void **obj, char **line, char *id, void *(build)(char **));
void	*build_ambient(char **line);
void	*build_camera(char **line);
void	*build_light(char **line);
void	*build_sphere(t_mlx *mlx, char **line);
void	*build_plane(t_mlx *mlx, char **line);
void	*build_cylinder(t_mlx *mlx, char **line);
void	*build_cone(t_mlx *mlx, char **line);

#endif

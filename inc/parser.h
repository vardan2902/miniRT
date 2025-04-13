/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:12:40 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/04/13 16:51:53 by ysaroyan         ###   ########.fr       */
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
void	*build_sphere(char **line);
void	*build_plane(char **line);
void	*build_cylinder(char **line);

#endif

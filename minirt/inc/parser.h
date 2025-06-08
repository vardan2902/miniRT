/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:12:40 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/06/08 17:27:58 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdbool.h>
# include <structs.h>

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

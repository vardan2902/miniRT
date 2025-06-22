/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:12:40 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/06/22 16:11:36 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <minirt.h>

bool	parse_line(t_scene *scene, char *identifier, char **line);
void	parse_scene(void *ptr, t_scene *scene, int fd);
bool	parse_object(void **obj, char **line, char *id, void *(build)(char **));
void	*build_ambient(char **line);
void	*build_camera(char **line);
void	*build_light(char **line);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 20:05:35 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/04/12 20:31:12 by ysaroyan         ###   ########.fr       */
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

#endif

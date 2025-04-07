/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 20:05:35 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/04/07 20:35:49 by ysaroyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <minirt.h>
# include <handlers.h>

int		validate_args(int argc, char **argv);
void	throw_error(char *msg);
void	init_mlx(t_mlx *mlx);
void	register_hooks(t_mlx *mlx);

#endif

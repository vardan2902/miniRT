/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:49:14 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/06/22 18:02:29 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# define WIDTH 1200
# define HEIGHT 1000
# define TITLE "miniRT"

# define EPSILON 0.0004f
# define BASE_SCALE 0.02f

# define AMBIENT "A"
# define CAMERA "C"
# define SPHERE "sp"
# define CYLINDER "cy"
# define PLANE "pl"

# define RATIO_MIN 0.0f
# define RATIO_MAX 1.0f
# define ORIENT_MIN -1.0f
# define ORIENT_MAX 1.0f
# define RGB_MIN 0.0f
# define RGB_MAX 255.0f
# define DEG_MIN 0.0f
# define DEG_MAX 180.0f
# define MIN_DIAMETER 1.0f
# define MAX_DIAMETER 100.0f
# define MIN_HEIGHT 1.0f
# define MAX_HEIGHT 300.0f

# define ERR_INVALID_TOKEN "miniRT: Invalid token: "
# define ERR_MALLOC "Error\nminiRT: malloc"
# define ERR_ID_DUP "miniRT: identifier duplication: "
# define ERR_MANDATORY_C "miniRT: mandatory property `C' not provided"
# define ERR_MANDATORY_A "miniRT: mandatory property `A' not provided"
# define ERR_MANDATORY_L "miniRT: mandatory property `L' not provided"
# define ERR_WRONG_ID "miniRT: wrong identifier: "
# define ERR_MLX_INIT "mlx: mlx_init failed"
# define ERR_MLX_WIN "mlx: mlx_new_window failed"
# define ERR_MLX_IMG "mlx: mlx_new_image failed"

#endif

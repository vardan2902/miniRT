/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:39:56 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/04/11 20:04:28 by ysaroyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <libft.h>

typedef struct s_mlx		t_mlx;
typedef struct s_rgb		t_rgb;
typedef struct s_ambient	t_ambient;
typedef struct s_vector		t_vector;
typedef struct s_camera		t_camera;
typedef struct s_light		t_light;
typedef struct s_sphere		t_sphere;
typedef struct s_plane		t_plane;
typedef struct s_cylinder	t_cylinder;
typedef struct s_scene		t_scene;

struct s_mlx
{
	void	*ptr;
	void	*win;
};

struct s_rgb
{
	unsigned char	r; // validate 0 - 255
	unsigned char	g;
	unsigned char	b;
};

struct s_ambient
{
	double	lighting; // ambient lighting ratio in the range [0.0,1.0]
	t_rgb	rgb;
};

struct s_vector
{
	double	x;
	double	y;
	double	z;
};

struct s_camera
{
	t_vector	position;
	t_vector	orientation; // for orientation range is [-1, 1]
	double		fov; // Horizontal field of view in degrees in the range [0,180]
};

struct s_light
{
	t_vector	position;
	double		brightness; //  the light brightness ratio in the range [0.0,1.0]
};

struct s_sphere
{
	t_vector	position;
	t_rgb		rgb;
	double		diameter;
};

struct s_plane
{
	t_vector	position;
	t_vector	orientation;
	t_rgb		rgb;
};

struct s_cylinder
{
	t_vector	position;
	t_vector	orientation;
	t_rgb		rgb;
	double		diameter;
	double		height;
};

struct s_scene
{
	t_camera	*camera;
	t_ambient	*ambient;
	t_light		*light;
	t_list		*sphere_list;
	t_list		*plane_list;
	t_list		*cylinder_list;
};

#endif

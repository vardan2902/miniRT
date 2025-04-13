/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:39:56 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/04/13 20:25:16 by vapetros         ###   ########.fr       */
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
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
};

struct s_ambient
{
	float	lighting;
	t_rgb	*rgb;
};

struct s_vector
{
	float	x;
	float	y;
	float	z;
};

struct s_camera
{
	t_vector	*position;
	t_vector	*orientation;
	float		fov;
};

struct s_light
{
	t_vector	*position;
	float		brightness;
};

struct s_sphere
{
	t_vector	*position;
	t_rgb		*rgb;
	float		diameter;
};

struct s_plane
{
	t_vector	*position;
	t_vector	*orientation;
	t_rgb		*rgb;
};

struct s_cylinder
{
	t_vector	*position;
	t_vector	*orientation;
	t_rgb		*rgb;
	float		diameter;
	float		height;
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

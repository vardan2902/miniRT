/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:39:56 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/04/25 17:36:49 by ysaroyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <libft.h>
# include <enums.h>

typedef struct s_mlx			t_mlx;
typedef struct s_rgb			t_rgb;
typedef struct s_ambient		t_ambient;
typedef struct s_vector			t_vector;
typedef struct s_camera			t_camera;
typedef struct s_light			t_light;
typedef struct s_sphere			t_sphere;
typedef struct s_plane			t_plane;
typedef struct s_cylinder		t_cylinder;
typedef struct s_object			t_object;
typedef struct s_hit			t_hit;
typedef struct s_ray			t_ray;
typedef struct s_coefficients	t_coefficients;
typedef struct s_scene			t_scene;
typedef struct s_viewport		t_viewport;
typedef struct s_basis			t_basis;
typedef struct s_ndc			t_ndc;
typedef struct s_img			t_img;
typedef struct s_mouse_state	t_mouse_state;

struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
};

struct s_mouse_state
{
	int			last_x;
	int			last_y;
	int			move_counter;
	bool		left_pressed;
	bool		right_pressed;
	t_object	*hit_object;
};

struct s_mlx
{
	void			*ptr;
	void			*win;
	t_img			*img;
	t_scene			*scene;
	t_mouse_state	mouse_state;
	bool			need_render;
	bool			interactive;
};

struct s_rgb
{
	int	r;
	int	g;
	int	b;
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

struct s_object
{
	enum e_object_types	type;
	void				*object;
};

struct s_hit
{
	float		t;
	t_vector	*position;
	t_vector	*orientation;
	t_object	*object;
};

struct s_ray
{
	t_vector	*position;
	t_vector	*orientation;
};

struct s_coefficients
{
	float	a;
	float	b;
	float	c;
};

struct s_scene
{
	t_camera	*camera;
	t_ambient	*ambient;
	t_light		*light;
	t_list		*object_list;
};

struct s_viewport
{
	float	width;
	float	height;
};

struct s_basis
{
	t_vector	*right;
	t_vector	*up;
	t_vector	*forward;
};

struct s_ndc
{
	float	u;
	float	v;
};

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 16:27:10 by vapetros          #+#    #+#             */
/*   Updated: 2025/06/22 20:10:51 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_BONUS_H
# define STRUCTS_BONUS_H

# include <minirt.h>
# include <mlx_int.h>

typedef struct s_mlx				t_mlx;
typedef struct s_rgb				t_rgb;
typedef struct s_ambient			t_ambient;
typedef struct s_vector				t_vector;
typedef struct s_camera				t_camera;
typedef struct s_light				t_light;
typedef struct s_sphere				t_sphere;
typedef struct s_plane				t_plane;
typedef struct s_cylinder			t_cylinder;
typedef struct s_cone				t_cone;
typedef struct s_object				t_object;
typedef struct s_hit				t_hit;
typedef struct s_ray				t_ray;
typedef struct s_coefficients		t_coefficients;
typedef struct s_scene				t_scene;
typedef struct s_viewport			t_viewport;
typedef struct s_basis				t_basis;
typedef struct s_ndc				t_ndc;
typedef struct s_mlx_img			t_mlx_img;
typedef struct s_cylinder_props		t_cylinder_props;
typedef struct s_cone_props			t_cone_props;
typedef struct s_light_effects		t_light_effects;
typedef struct s_cylinder_cap		t_cylinder_cap;
typedef struct s_bumpmap			t_bumpmap;
typedef struct s_check_cap_props	t_check_cap_props;
typedef struct s_roots				t_roots;
typedef struct s_color_props		t_color_props;
typedef struct s_map_props			t_map_props;

struct s_color_props
{
	t_hit	*hit;
	t_rgb	*obj_color;
};

struct s_bumpmap
{
	int	width;
	int	height;
	int	*pixels;
};

struct s_mlx_img
{
	t_img	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
};

struct s_mlx
{
	void			*ptr;
	void			*win;
	t_mlx_img		*img;
	t_scene			*scene;
	t_object		*hit_object;
	int				action;
	int				axis;
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
	t_vector	up;
	float		fov;
};

struct s_light
{
	t_vector	*position;
	float		brightness;
	t_rgb		*rgb;
};

struct s_sphere
{
	t_vector	*position;
	t_rgb		*rgb;
	t_bumpmap	*bumpmap;
	float		diameter;
	float		initial_diameter;
};

struct s_plane
{
	t_vector	*position;
	t_vector	*orientation;
	t_rgb		*rgb;
	t_bumpmap	*bumpmap;
};

struct s_cylinder
{
	t_vector	*position;
	t_vector	*orientation;
	t_rgb		*rgb;
	t_bumpmap	*bumpmap;
	float		diameter;
	float		height;
	float		initial_diameter;
	float		initial_height;
};

struct s_cone
{
	t_vector	*position;
	t_vector	*orientation;
	t_rgb		*rgb;
	t_bumpmap	*bumpmap;
	float		diameter;
	float		height;
	float		initial_diameter;
	float		initial_height;
};

struct s_object
{
	enum e_object_types	type;
	void				*object;
	bool				checkerboard;
};

struct s_hit
{
	float		t;
	t_vector	position;
	t_vector	orientation;
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

struct s_basis
{
	t_vector	right;
	t_vector	up;
	t_vector	forward;
};

struct s_scene
{
	t_camera	*camera;
	t_ambient	*ambient;
	t_list		*lights;
	t_list		*object_list;
	t_mlx		*mlx;
};

struct s_viewport
{
	float	width;
	float	height;
};

struct s_ndc
{
	float	u;
	float	v;
};

struct s_roots
{
	float	t1;
	float	t2;
};

struct s_cylinder_props
{
	t_roots		roots;
	t_hit		side_hit;
	t_hit		cap_hit;
	bool		side_ok;
	bool		cap_ok;
	t_vector	axis;
};

struct s_cone_props
{
	bool		side_ok;
	bool		cap_ok;
	float		t_side;
	float		t_cap;
	t_roots		roots;
	t_vector	p_side;
	t_vector	apex_to_p;
};

struct s_cylinder_cap
{
	t_vector	center;
	t_vector	normal;
};

struct s_check_cap_props
{
	t_vector	oc;
	t_vector	p;
	t_vector	diff;
	float		radius_sq;
	float		t;
	float		dist_sq;
	bool		hit_found;
};

struct s_light_effects
{
	float	diffuse;
	float	specular;
	float	attenuation;
	bool	in_shadow;
};

struct	s_map_props
{
	t_vector	n;
	float		u;
	float		v;
	t_rgb		color;
	t_vector	sampled;
	t_vector	bumped;
	t_vector	tangent;
	t_vector	bitangent;
};

#endif

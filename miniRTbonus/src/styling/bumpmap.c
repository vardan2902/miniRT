#include <minirt.h>

static t_vector	get_bumped_sphere_orient(t_hit *hit, t_sphere *sphere)
{
	if (!sphere->bumpmap)
		return hit->orientation;

	t_vector n = v_normalize(v_sub(hit->position, *sphere->position));

	float u = (0.5f + atan2f(n.z, n.x) / (2.0f * M_PI)) * 3.0f;
	float v = (0.5f - asinf(n.y) / M_PI) * 3.0f;

	t_rgb color = get_color_from_bumpmap(sphere->bumpmap, u, v);

	t_vector sampled_normal = {
		(color.r / 255.0f) * 2.0f - 1.0f,
		(color.g / 255.0f) * 2.0f - 1.0f,
		(color.b / 255.0f) * 2.0f - 1.0f};

	t_vector up = fabsf(n.y) < 0.99f ? (t_vector){0, 1, 0} : (t_vector){1, 0, 0};
	t_vector tangent = v_normalize(v_cross_product(up, n));
	t_vector bitangent = v_normalize(v_cross_product(n, tangent));

	t_vector bumped_normal = v_add(
		v_add(
			v_scalar_product(tangent, sampled_normal.x),
			v_scalar_product(bitangent, sampled_normal.y)),
		v_scalar_product(n, sampled_normal.z));

	return v_normalize(bumped_normal);
}

static t_vector get_bumped_plane_orient(t_hit *hit, t_plane *plane) {
	if (!plane->bumpmap)
		return hit->orientation;

	t_vector n = v_normalize(*plane->orientation);
	t_vector up = fabsf(n.y) < 0.99f ? (t_vector){0, 1, 0} : (t_vector){1, 0, 0};
	t_vector tangent = v_normalize(v_cross_product(up, n));
	t_vector bitangent = v_normalize(v_cross_product(n, tangent));

	t_vector local = v_sub(hit->position, *plane->position);
	float u = v_dot_product(local, tangent);
	float v = v_dot_product(local, bitangent);

	float uv_scale = 0.1f;
	u *= uv_scale;
	v *= uv_scale;
	u = u - floorf(u);
	v = v - floorf(v);

	t_rgb color = get_color_from_bumpmap(plane->bumpmap, u, v);
	t_vector sampled_normal = {
		(color.r / 255.0f) * 2.0f - 1.0f,
		(color.g / 255.0f) * 2.0f - 1.0f,
		(color.b / 255.0f) * 2.0f - 1.0f
	};

	t_vector bumped_normal = v_add(
		v_add(
			v_scalar_product(tangent, sampled_normal.x),
			v_scalar_product(bitangent, sampled_normal.y)
		),
		v_scalar_product(n, sampled_normal.z)
	);

	return v_normalize(bumped_normal);
}

static t_vector get_bumped_cylinder_orient(t_hit *hit, t_cylinder *cylinder)
{
	if (!cylinder->bumpmap)
		return (hit->orientation);

	t_vector n = hit->orientation;

	t_vector axis = v_normalize(*cylinder->orientation);
	t_vector tangent = v_normalize(v_cross_product(axis, (t_vector){0, 1, 0}));
	if (v_length(tangent) == 0)
		tangent = v_normalize(v_cross_product(axis, (t_vector){1, 0, 0}));
	t_vector bitangent = v_normalize(v_cross_product(n, tangent));

	t_vector hit_vec = v_sub(hit->position, *cylinder->position);
	t_vector p = v_sub(hit_vec, v_scalar_product(axis, v_dot_product(hit_vec, axis)));

	float u = (0.5f + atan2f(p.z, p.x) / (2 * M_PI)) * 3.0f;
	float v = (v_dot_product(hit_vec, axis) / cylinder->height) * 3.0f;
	if (u < 0) u += 1.0f;

	t_rgb bump = get_color_from_bumpmap(cylinder->bumpmap, u, v);

	t_vector map_normal = {
		(bump.r / 255.0f) * 2.0f - 1.0f,
		(bump.g / 255.0f) * 2.0f - 1.0f,
		(bump.b / 255.0f) * 2.0f - 1.0f
	};

	t_vector bumped = {
		map_normal.x * tangent.x + map_normal.y * bitangent.x + map_normal.z * n.x,
		map_normal.x * tangent.y + map_normal.y * bitangent.y + map_normal.z * n.y,
		map_normal.x * tangent.z + map_normal.y * bitangent.z + map_normal.z * n.z
	};

	return v_normalize(bumped);
}

static t_vector get_bumped_cone_orient(t_hit *hit, t_cone *cone)
{
	if (!cone->bumpmap)
		return (hit->orientation);

	t_vector n = hit->orientation;
	t_vector axis = v_normalize(*cone->orientation);

	t_vector tangent = v_normalize(v_cross_product(axis, (t_vector){0, 1, 0}));
	if (v_length(tangent) == 0)
		tangent = v_normalize(v_cross_product(axis, (t_vector){1, 0, 0}));
	t_vector bitangent = v_normalize(v_cross_product(n, tangent));

	t_vector hit_vec = v_sub(hit->position, *cone->position);
	float height_proj = v_dot_product(hit_vec, axis);

	t_vector radial = v_sub(hit_vec, v_scalar_product(axis, height_proj));
	float u = 0.5f + atan2f(radial.z, radial.x) / (2 * M_PI);
	if (u < 0) u += 1.0f;

	float v = height_proj / cone->height;
	v = fminf(fmaxf(v, 0.0f), 1.0f);

	t_rgb bump = get_color_from_bumpmap(cone->bumpmap, u, v);
	t_vector map_normal = {
		(bump.r / 255.0f) * 2.0f - 1.0f,
		(bump.g / 255.0f) * 2.0f - 1.0f,
		(bump.b / 255.0f) * 2.0f - 1.0f
	};

	t_vector bumped = {
		map_normal.x * tangent.x + map_normal.y * bitangent.x + map_normal.z * n.x,
		map_normal.x * tangent.y + map_normal.y * bitangent.y + map_normal.z * n.y,
		map_normal.x * tangent.z + map_normal.y * bitangent.z + map_normal.z * n.z
	};

	return v_normalize(bumped);
}

t_vector get_bumped_orient(t_hit *hit)
{
	t_object *object;

	object = (t_object *)hit->object;
	if (object->type == E_SPHERE)
		return (get_bumped_sphere_orient(hit, (t_sphere *)object->object));
	else if (object->type == E_PLANE)
		return (get_bumped_plane_orient(hit, (t_plane *)object->object));
	else if (object->type == E_CYLINDER)
		return (get_bumped_cylinder_orient(hit, (t_cylinder *)object->object));
	else if (object->type == E_CONE)
		return (get_bumped_cone_orient(hit, (t_cone *)object->object));
	else
		return ((t_vector){0, 0, 0});
}

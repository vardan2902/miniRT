#include <minirt.h>

static void	print_vector(const char *name, t_vector vec)
{
	printf("\t%s: (%.2f, %.2f, %.2f)\n", name, vec.x, vec.y, vec.z);
}

static void	print_rgb(t_rgb rgb)
{
	printf("\tRGB: (%hhu, %hhu, %hhu)\n", rgb.r, rgb.g, rgb.b);
}

static void	print_sphere(t_sphere *sp)
{
	printf("Sphere:\n");
	print_vector("Position", sp->position);
	printf("\tDiameter: %.2f\n", sp->diameter);
	print_rgb(sp->rgb);
}

static void	print_plane(t_plane *pl)
{
	printf("Plane:\n");
	print_vector("Position", pl->position);
	print_vector("Orientation", pl->orientation);
	print_rgb(pl->rgb);
}

static void	print_cylinder(t_cylinder *cy)
{
	printf("Cylinder:\n");
	print_vector("Position", cy->position);
	print_vector("Orientation", cy->orientation);
	printf("\tDiameter: %.2f\n", cy->diameter);
	printf("\tHeight: %.2f\n", cy->height);
	print_rgb(cy->rgb);
}

void	print_scene(t_scene *scene)
{
	if (!scene)
	{
		printf("Scene is NULL\n");
		return;
	}

	printf("=== Scene Configuration ===\n");

	// Print Camera
	if (scene->camera)
	{
		printf("[Camera]\n");
		print_vector("Position", scene->camera->position);
		print_vector("Orientation", scene->camera->orientation);
		printf("\tFOV: %.2f\n", scene->camera->fov);
	}

	// Print Ambient Light
	if (scene->ambient)
	{
		printf("[Ambient Light]\n");
		printf("\tRatio: %.2f\n", scene->ambient->lighting);
		print_rgb(scene->ambient->rgb);
	}

	// Print Light
	if (scene->light)
	{
		printf("[Light]\n");
		print_vector("Position", scene->light->position);
		printf("\tBrightness: %.2f\n", scene->light->brightness);
	}

	// Print Spheres
	if (scene->sphere_list)
	{
		printf("\n[Spheres]\n");
		for (t_list *node = scene->sphere_list; node; node = node->next)
			print_sphere((t_sphere *)node->content);
	}

	// Print Planes
	if (scene->plane_list)
	{
		printf("\n[Planes]\n");
		for (t_list *node = scene->plane_list; node; node = node->next)
			print_plane((t_plane *)node->content);
	}

	// Print Cylinders
	if (scene->cylinder_list)
	{
		printf("\n[Cylinders]\n");
		for (t_list *node = scene->cylinder_list; node; node = node->next)
			print_cylinder((t_cylinder *)node->content);
	}

	printf("===========================\n");
}

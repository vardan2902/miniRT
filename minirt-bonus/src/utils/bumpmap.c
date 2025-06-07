#include <minirt.h>

float	get_bump_height(t_bumpmap *bumpmap, float u, float v)
{
	if (!bumpmap || !bumpmap->pixels)
		return 0.0f;

	int x = (int)(u * bumpmap->width) % bumpmap->width;
	int y = (int)(v * bumpmap->height) % bumpmap->height;

	int color = bumpmap->pixels[y * bumpmap->width + x];
	int r = (color >> 16) & 0xFF;

	return (r / 255.0f);
}

t_rgb	get_color_from_bumpmap(t_bumpmap *bumpmap, float u, float v)
{
	t_rgb	color;
	int		pixel;
	int		x;
	int		y;

	x = (int)(u * bumpmap->width) % bumpmap->width;
	y = (int)(v * bumpmap->height) % bumpmap->height;
	if (x < 0)
		x += bumpmap->width;
	if (y < 0)
		y += bumpmap->height;
	pixel = bumpmap->pixels[y * bumpmap->width + x];
	color.r = (pixel >> 16) & 0xFF;
	color.g = (pixel >> 8) & 0xFF;
	color.b = (pixel) & 0xFF;
	return (color);
}

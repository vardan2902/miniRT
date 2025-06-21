/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unique_instructions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 18:54:15 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/06/21 20:20:53 by ysaroyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

bool	set_prop(char *str, float *prop)
{
	if (!is_in_limit(str, -FLT_MAX, FLT_MAX) || !to_float(str, prop))
	{
		log_error(ERR_INVALID_TOKEN, str);
		return (false);
	}
	return (true);
}

static void	get_map_pixels(t_bumpmap **bumpmap, t_img *img)
{
	int		bpp;
	int		size_line;
	int		endian;

	(*bumpmap)->pixels = (int *)mlx_get_data_addr(img, &bpp,
			&size_line, &endian);
	free(img->image);
	free(img);
}

bool	set_bumpmap(t_mlx *mlx, char *line, t_bumpmap **bumpmap)
{
	char	**splitted;
	t_img	*img;

	splitted = ft_split(line, ':');
	if (!splitted)
		return (false);
	if (ft_strcmp(splitted[0], BUMPMAP))
		return (log_error(ERR_INVALID_TOKEN, splitted[0]),
			free_splitted(splitted), false);
	if (access(splitted[1], F_OK) != 0 || !splitted[1]
		|| !ft_strchr(splitted[1], '/'))
		return (log_error(ERR_MAP, splitted[1]),
			free_splitted(splitted), false);
	*bumpmap = (t_bumpmap *)malloc(sizeof(t_bumpmap));
	if (!*bumpmap)
		return (false);
	img = mlx_xpm_file_to_image(mlx->ptr, splitted[1],
			&(*bumpmap)->width, &(*bumpmap)->height);
	if (!img)
		return (free(bumpmap), false);
	free_splitted(splitted);
	get_map_pixels(bumpmap, img);
	return (true);
}

bool	assign_light_list(t_scene *scene, char **line,
	void *(build)(char **))
{
	t_list	*new;
	t_light	*light;

	light = build(line);
	new = ft_lstnew(light);
	if (!new)
		return (false);
	ft_lstadd_back(&scene->lights, new);
	return (true);
}

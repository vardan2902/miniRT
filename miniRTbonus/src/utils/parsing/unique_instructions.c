/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unique_instructions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 18:54:15 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/05/18 13:18:45 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

bool set_prop(char *str, float *prop)
{
    if (!is_in_limit(str, -FLT_MAX, FLT_MAX) || !to_float(str, prop))
    {
        log_error(ERR_INVALID_TOKEN, str);
        return (false);
    }
    return (true);
}

bool set_bumpmap(t_mlx *mlx, char *line, t_bumpmap **bumpmap)
{
    int bpp;
    int size_line;
    int endian;
    void *img;
    char **splitted;

    splitted = ft_split(line, ':');
    if (!splitted)
        return (false);
    if (ft_strcmp(splitted[0], BUMPMAP))
    {
        log_error(ERR_INVALID_TOKEN, splitted[0]);
        return (free_splitted(splitted), false);
    }
    if (access(splitted[1], F_OK) != 0 || !splitted[1] || !ft_strchr(splitted[1], '/'))
    {
        log_error("Bump map file error: ", splitted[1]);
        return (free_splitted(splitted), false);
    }
    *bumpmap = (t_bumpmap *)malloc(sizeof(t_bumpmap));
    if (!*bumpmap)
        return (false);
    img = mlx_xpm_file_to_image(mlx->ptr, splitted[1], &(*bumpmap)->width, &(*bumpmap)->height);
    if (!img)
        return (false);
    free_splitted(splitted);
    (*bumpmap)->pixels = (int *)mlx_get_data_addr(img, &bpp, &size_line, &endian);
    return (true);
}

bool	assign_light_list(t_scene *scene, char **line,
	void *(build)(char **))
{
	t_list  *new;
	t_light *light;

	light = build(line);
	new = ft_lstnew(light);
	if (!new)
		return (false);
	ft_lstadd_back(&scene->lights, new);
	return (true);
}

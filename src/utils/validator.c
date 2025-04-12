/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 19:56:36 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/04/12 18:55:14 by ysaroyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static void	validate_extension(char *path)
{
	char	*ext;

	ext = ft_strrchr(path, '.');
	if (!ext)
		throw_error("");
	if (path >= ext || ft_strcmp(ext, ".rt"))
		throw_error("");
}

static int	validate_file(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		throw_error("");
	return (fd);
}

int	validate_args(int argc, char **argv)
{
	if (argc != 2)
		throw_error("");
	validate_extension(argv[1]);
	return (validate_file(argv[1]));
}

bool	is_line_empty(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
		if (!ft_isspace(line[i]))
			return (false);
	return (true);
}

bool	is_identifier(char *str)
{
	return (!ft_strcmp(str, AMBIENT) || !ft_strcmp(str, CAMERA)
		|| !ft_strcmp(str, LIGHT) || !ft_strcmp(str, SPHERE)
		|| !ft_strcmp(str, CYLINDER) || !ft_strcmp(str, PLANE));
}

bool	is_instruction_in_range(char **inst, double min,
	double max, int size)
{
	int	i;

	i = -1;
	while (inst[++i])
		if (!is_in_limit(inst[i], min, max))
			return (false);
	return (i == size);
}

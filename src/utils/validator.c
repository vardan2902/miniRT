/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 19:56:36 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/04/07 20:29:46 by ysaroyan         ###   ########.fr       */
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

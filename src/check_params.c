/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarneir <acarneir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 19:44:23 by rfelipe-          #+#    #+#             */
/*   Updated: 2022/10/12 21:37:01 by acarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	open_fd(char *file)
{
	int		fd;
	char	*path;

	path = ft_strjoin("./maps/", file);
	fd = open(path, O_RDWR);
	free(path);
	return (fd);
}

void	check_params(int argc, char *argv[])
{
	int		fd;

	if (argc == 2)
	{
		if (ft_strncmp(argv[1] + (ft_strlen(argv[1]) - 4), ".cub", 4) != 0)
			throw_error("You must enter a '.cub' file", NULL);
	}
	else
		throw_error("Invalid numbers of arguments", NULL);
	fd = open_fd(argv[1]);
	if (fd < 0)
		throw_error("A valid file was not found", NULL);
	close(fd);
}

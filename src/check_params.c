/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfelipe- <rfelipe-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 19:44:23 by rfelipe-          #+#    #+#             */
/*   Updated: 2022/10/10 21:23:15 by rfelipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	check_params(int argc, char *argv[])
{
	int	fd;

	if (argc == 2)
	{
		if (ft_strncmp(argv[1] + (ft_strlen(argv[1]) - 4), ".cub", 4) != 0)
			throw_error("You must enter a '.cub' file");
	}
	else
		throw_error("Invalid numbers of arguments");
	fd = open(ft_strjoin("./maps/", argv[1]), O_RDWR);
	if (fd < 0)
		throw_error("A valid file was not found");
	close(fd);
}

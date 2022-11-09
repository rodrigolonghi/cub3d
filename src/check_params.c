/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarneir <acarneir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 19:44:23 by rfelipe-          #+#    #+#             */
/*   Updated: 2022/11/08 20:14:13 by acarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	save_colors(t_game *game, char id, char *color, int fd)
{
	int		error;
	char	**matrix;

	error = FALSE;
	if (id == 'f')
	{
		if (game->floor.r == -1)
		{
			matrix = ft_split(color, ',');
			game->floor = create_color(ft_atoi(matrix[0]), ft_atoi(matrix[1]),
					ft_atoi(matrix[2]));
			ft_free_char_matrix(matrix);
		}
		else
			error = TRUE;
	}
	else if (id == 'c')
	{
		if (game->ceilling.r == -1)
		{
			matrix = ft_split(color, ',');
			game->ceilling = create_color(ft_atoi(matrix[0]),
					ft_atoi(matrix[1]), ft_atoi(matrix[2]));
			ft_free_char_matrix(matrix);
		}
		else
			error = TRUE;
	}
	if (error)
	{
		close(fd);
		throw_error("Invalid colors!", game);
	}
}

static void	save_texture(t_game *game, char id, char *path, int fd)
{
	int	error;

	error = FALSE;
	if (id == 'n')
	{
		if (game->no.addr == NULL)
			game->no.addr = ft_strdup(path);
		else
			error = TRUE;
	}
	else if (id == 's' && !error)
	{
		if (game->so.addr == NULL)
			game->so.addr = ft_strdup(path);
		else
			error = TRUE;
	}
	else if (id == 'e' && !error)
	{
		if (game->ea.addr == NULL)
			game->ea.addr = ft_strdup(path);
		else
			error = TRUE;
	}
	else if (id == 'w' && !error)
	{
		if (game->we.addr == NULL)
			game->we.addr = ft_strdup(path);
		else
			error = TRUE;
	}
	if (error)
	{
		close(fd);
		throw_error("You need to choose only one texture per path", game);
	}
}

static int	is_valid_error(t_game *game)
{
	if (game->no.addr == NULL || game->so.addr == NULL || game->ea.addr == NULL
		|| game->we.addr == NULL || game->ceilling.r == -1
		|| game->floor.r == -1)
		return (TRUE);
	return (FALSE);
}

static void	get_file_data(t_game *game, int fd)
{
	int		error;
	char	*aux;
	char	**matrix;
	char	*temp;

	error = FALSE;
	while (get_next_line(fd, &aux) == 1 && !error)
	{
		if (ft_strlen(aux) == 0)
		{
			if (aux != NULL)
				free(aux);
			continue ;
		}
		temp = ft_strtrim(aux, " \t");
		matrix = ft_split(temp, ' ');
		if (!ft_strncmp("NO", matrix[0], 2) && ft_strlen(matrix[0]) == 2)
			save_texture(game, 'n', matrix[1], fd);
		else if (!ft_strncmp("SO", matrix[0], 2) && ft_strlen(matrix[0]) == 2)
			save_texture(game, 's', matrix[1], fd);
		else if (!ft_strncmp("EA", matrix[0], 2) && ft_strlen(matrix[0]) == 2)
			save_texture(game, 'e', matrix[1], fd);
		else if (!ft_strncmp("WE", matrix[0], 2) && ft_strlen(matrix[0]) == 2)
			save_texture(game, 'w', matrix[1], fd);
		else if (!ft_strncmp("F", matrix[0], 1) && ft_strlen(matrix[0]) == 1)
			save_colors(game, 'f', matrix[1], fd);
		else if (!ft_strncmp("C", matrix[0], 1) && ft_strlen(matrix[0]) == 1)
			save_colors(game, 'c', matrix[1], fd);
		else
			error = TRUE;
		if (aux != NULL)
			free(aux);
		free(temp);
		ft_free_char_matrix(matrix);
	}
	if (aux != NULL)
		free(aux);
	if (error && is_valid_error(game))
	{
		close(fd);
		throw_error("Invalid .cub file!", game);
	}
	else if (error)
	{
		while (get_next_line(fd, &aux) == 1)
		{
			if (aux != NULL)
				free(aux);
		}
		if (aux != NULL)
			free(aux);
	}
}

int	open_fd(char *file)
{
	int		fd;
	char	*path;

	path = ft_strjoin("./maps/", file);
	fd = open(path, O_RDWR);
	free(path);
	return (fd);
}

static void	validade_file_data(t_game *g)
{
	printf("no.addr = '%s'\n", g->no.addr);
	g->no.img.ptr = mlx_xpm_file_to_image(g->mlx, g->no.addr, &g->no.width, &g->no.height);
	g->so.img.ptr = mlx_xpm_file_to_image(g->mlx, g->so.addr, &g->so.width, &g->so.height);
	g->ea.img.ptr = mlx_xpm_file_to_image(g->mlx, g->ea.addr, &g->ea.width, &g->ea.height);
	g->we.img.ptr = mlx_xpm_file_to_image(g->mlx, g->we.addr, &g->we.width, &g->we.height);
	g->no.img.data = mlx_get_data_addr(g->no.img.ptr, &g->no.img.bits_per_pixel, &g->no.img.line_length, &g->no.img.endian);
	g->so.img.data = mlx_get_data_addr(g->so.img.ptr, &g->so.img.bits_per_pixel, &g->so.img.line_length, &g->so.img.endian);
	g->ea.img.data = mlx_get_data_addr(g->ea.img.ptr, &g->ea.img.bits_per_pixel, &g->ea.img.line_length, &g->ea.img.endian);
	g->we.img.data = mlx_get_data_addr(g->we.img.ptr, &g->we.img.bits_per_pixel, &g->we.img.line_length, &g->we.img.endian);
	if (g->floor.r > 255 || g->floor.r < 0 || g->floor.g > 255 || g->floor.g < 0
		|| g->floor.b > 255 || g->floor.b < 0 || g->ceilling.r > 255
		|| g->ceilling.r < 0 || g->ceilling.g > 255 || g->ceilling.g < 0
		|| g->ceilling.b > 255 || g->ceilling.b < 0)
		throw_error("Invalid color!", g);
}

void	check_params(t_game *game, int argc, char *argv[])
{
	int	fd;

	if (argc == 2)
	{
		if (ft_strncmp(argv[1] + (ft_strlen(argv[1]) - 4), ".cub", 4) != 0)
			throw_error("You must enter a '.cub' file", NULL);
	}
	else
		throw_error("Invalid numbers of arguments", NULL);
	fd = open_fd(argv[1]);
	if (fd < 0)
	{
		close(fd);
		throw_error("A valid file was not found", NULL);
	}
	get_file_data(game, fd);
	close(fd);
	validade_file_data(game);
}

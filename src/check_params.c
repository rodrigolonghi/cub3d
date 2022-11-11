/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarneir <acarneir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 19:44:23 by rfelipe-          #+#    #+#             */
/*   Updated: 2022/11/10 23:46:56 by acarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	save_colors(t_game *game, char id, char *color, int fd)
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
	// if (error)
	// {
	// 	close(fd);
	// 	throw_error("Invalid colors!", game);
	// }
	if(fd)
	{
		
	}
	return (error);
}

static int save_texture(t_game *game, char id, char *path, int fd)
{
	int	error;

	error = FALSE;
	if (id == 'n')
	{
		if (game->texture[0].addr == NULL)
			game->texture[0].addr = ft_strdup(path);
		else
			error = TRUE;
	}
	else if (id == 's' && !error)
	{
		if (game->texture[1].addr == NULL)
			game->texture[1].addr = ft_strdup(path);
		else
			error = TRUE;
	}
	else if (id == 'e' && !error)
	{
		if (game->texture[2].addr == NULL)
			game->texture[2].addr = ft_strdup(path);
		else
			error = TRUE;
	}
	else if (id == 'w' && !error)
	{
		if (game->texture[3].addr == NULL)
			game->texture[3].addr = ft_strdup(path);
		else
			error = TRUE;
	}
	// if (error)
	// {
	// 	close(fd);
	// 	throw_error("You need to choose only one texture per path", game);
	// }
	if(fd)
	{
		
	}
	return (error);
}

static int	is_valid_end(t_game *game)
{
	if (game->texture[0].addr == NULL || game->texture[1].addr == NULL || game->texture[2].addr == NULL
		|| game->texture[3].addr == NULL || game->ceilling.r == -1
		|| game->floor.r == -1)
		return (FALSE);
	return (TRUE);
}

static void	get_file_data(t_game *game, int fd)
{
	int		error;
	int		has_ended;
	char	*aux;
	char	**matrix;
	char	*temp;

	error = FALSE;
	has_ended = FALSE;
	while (!has_ended && !error && get_next_line(fd, &aux) == 1)
	{
		printf("aux = '%s'\n", aux);
		if (ft_strlen(aux) == 0)
		{
			if (aux != NULL)
				ft_free_ptr((void *)&aux);
			continue ;
		}
		temp = ft_strtrim(aux, " \t");
		matrix = ft_split(temp, ' ');
		if (!ft_strncmp("NO", matrix[0], 2) && ft_strlen(matrix[0]) == 2)
			error = save_texture(game, 'n', matrix[1], fd);
		else if (!ft_strncmp("SO", matrix[0], 2) && ft_strlen(matrix[0]) == 2)
			error = save_texture(game, 's', matrix[1], fd);
		else if (!ft_strncmp("EA", matrix[0], 2) && ft_strlen(matrix[0]) == 2)
			error = save_texture(game, 'e', matrix[1], fd);
		else if (!ft_strncmp("WE", matrix[0], 2) && ft_strlen(matrix[0]) == 2)
			error = save_texture(game, 'w', matrix[1], fd);
		else if (!ft_strncmp("F", matrix[0], 1) && ft_strlen(matrix[0]) == 1)
			error = save_colors(game, 'f', matrix[1], fd);
		else if (!ft_strncmp("C", matrix[0], 1) && ft_strlen(matrix[0]) == 1)
			error = save_colors(game, 'c', matrix[1], fd);
		else
		{
			if (!map_started(aux) && ft_strlen(aux) != 0)
				error = TRUE;
			has_ended = TRUE;
		}
		ft_free_char_matrix(matrix);
		ft_free_ptr((void *)&temp);
		ft_free_ptr((void *)&aux);
	}
	if (error || !is_valid_end(game))
	{
		while (get_next_line(fd, &aux) == 1)
		{
			if (aux != NULL)
				ft_free_ptr((void *)&aux);
		}
		if (aux != NULL)
			ft_free_ptr((void *)&aux);
		close(fd);
		throw_error("Invalid .cub file!", game);
	}
	else if (has_ended)
	{
		while (get_next_line(fd, &aux) == 1)
		{
			if (aux != NULL)
				ft_free_ptr((void *)&aux);
		}
		if (aux != NULL)
			ft_free_ptr((void *)&aux);
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
	int	i;

	i = 0;
	while (i < 4)
	{
		g->texture[i].img.ptr = mlx_xpm_file_to_image(g->mlx, g->texture[i].addr, &g->texture[i].width, &g->texture[i].height);
		if (!g->texture[i].img.ptr)
			throw_error("Invalid texture!", g);
		g->texture[i].img.data = mlx_get_data_addr(g->texture[i].img.ptr, &g->texture[i].img.bits_per_pixel, &g->texture[i].img.line_length, &g->texture[i].img.endian);
		if (!g->texture[i].img.data)
			throw_error("Invalid texture!", g);
		i++;
	}
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

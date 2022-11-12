/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarneir <acarneir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 19:44:23 by rfelipe-          #+#    #+#             */
/*   Updated: 2022/11/11 21:22:23 by acarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	save_file_data(t_game *game, char *aux, int *has_ended)
{
	char	*temp;
	char	**matrix;

	temp = ft_strtrim(aux, " \t");
	matrix = ft_split(temp, ' ');
	if (!ft_strncmp("NO", matrix[0], 2) && ft_strlen(matrix[0]) == 2)
		save_n_s_texture(game, 'n', matrix[1]);
	else if (!ft_strncmp("SO", matrix[0], 2) && ft_strlen(matrix[0]) == 2)
		save_n_s_texture(game, 's', matrix[1]);
	else if (!ft_strncmp("EA", matrix[0], 2) && ft_strlen(matrix[0]) == 2)
		save_e_w_texture(game, 'e', matrix[1]);
	else if (!ft_strncmp("WE", matrix[0], 2) && ft_strlen(matrix[0]) == 2)
		save_e_w_texture(game, 'w', matrix[1]);
	else if (!ft_strncmp("F", matrix[0], 1) && ft_strlen(matrix[0]) == 1)
		save_colors(game, 'f', matrix[1]);
	else if (!ft_strncmp("C", matrix[0], 1) && ft_strlen(matrix[0]) == 1)
		save_colors(game, 'c', matrix[1]);
	else
	{
		if (!map_started(aux) && ft_strlen(aux) != 0)
			game->error = TRUE;
		has_ended[0] = TRUE;
	}
	ft_free_char_matrix(matrix);
	ft_free_ptr((void *)&temp);
}

static void	get_file_data(t_game *game, int fd)
{
	int		has_ended[1];
	char	*aux;

	has_ended[0] = FALSE;
	while (!has_ended[0] && !game->error && get_next_line(fd, &aux) == 1)
	{
		if (ft_strlen(aux) == 0)
		{
			if (aux != NULL)
				ft_free_ptr((void *)&aux);
			continue ;
		}
		save_file_data(game, aux, has_ended);
		ft_free_ptr((void *)&aux);
	}
	if (has_ended[0] == FALSE && !game->error)
		game->error = TRUE;
	if (aux != NULL)
		ft_free_ptr((void *)&aux);
	read_until_end(fd);
	if (game->error || !is_valid_end(game))
	{
		close(fd);
		throw_error("Invalid .cub file!", game);
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
		g->file.texture[i].img.ptr = mlx_xpm_file_to_image(g->mlx,
				g->file.texture[i].addr, &g->file.texture[i].width,
				&g->file.texture[i].height);
		if (!g->file.texture[i].img.ptr)
			throw_error("Invalid texture!", g);
		g->file.texture[i].img.data = mlx_get_data_addr(g->file.texture[i].img
				.ptr, &g->file.texture[i].img.bits_per_pixel, &g->file
				.texture[i].img.line_length, &g->file.texture[i].img.endian);
		if (!g->file.texture[i].img.data)
			throw_error("Invalid texture!", g);
		i++;
	}
	if (g->file.floor.r > 255 || g->file.floor.r < 0 || g->file.floor.g > 255
		|| g->file.floor.g < 0 || g->file.floor.b > 255 || g->file.floor.b < 0
		|| g->file.ceilling.r > 255 || g->file.ceilling.r < 0
		|| g->file.ceilling.g > 255 || g->file.ceilling.g < 0
		|| g->file.ceilling.b > 255 || g->file.ceilling.b < 0)
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

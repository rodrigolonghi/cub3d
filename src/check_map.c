/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarneir <acarneir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 19:47:13 by rfelipe-          #+#    #+#             */
/*   Updated: 2022/11/10 23:50:09 by acarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	map_started(char *line)
{
	int	aux;

	if (ft_strlen(line) == 0)
		return (FALSE);
	aux = 0;
	while (line[aux])
	{
		if (!ft_strchr(" 01NSWE", line[aux]))
			return (FALSE);
		aux++;
	}
	return (TRUE);
}

static void	save_player(t_game *game, int rows, int cols)
{
	game->player_pos = create_vector(cols + 0.5, rows + 0.5);
	game->player_dir = create_vector(0.0, -1.0);
	game->camera_plane = create_vector(0.66, 0.0);
	if (game->map.coordinates[rows][cols] == 'N')
	{
		game->player_dir = vector_rotation(game->player_dir, 0, 1);
		game->camera_plane = vector_rotation(game->camera_plane, 0, 1);
	}
	else if (game->map.coordinates[rows][cols] == 'S')
	{
		game->player_dir = vector_rotation(game->player_dir, M_PI, 1);
		game->camera_plane = vector_rotation(game->camera_plane, M_PI, 1);
	}
	else if (game->map.coordinates[rows][cols] == 'W')
	{
		game->player_dir = vector_rotation(game->player_dir, M_PI / 2, 1);
		game->camera_plane = vector_rotation(game->camera_plane, M_PI / 2, 1);
	}
	else if (game->map.coordinates[rows][cols] == 'E')
	{
		game->player_dir = vector_rotation(game->player_dir, M_PI / 2, -1);
		game->camera_plane = vector_rotation(game->camera_plane, M_PI / 2, -1);
	}
	printf("pDir = [%f, %f] \n", game->player_dir.x, game->player_dir.y);
}

static int	is_valid_cell(t_game *game, int rows, int cols)
{
	if (rows < 0 || rows > (game->map.rows - 1)
		|| cols < 0 || cols > (game->map.cols - 1))
		return (FALSE);
	return (TRUE);
}

static void	check_surroundings(t_game *game, int rows, int cols)
{
	int		col_offset;
	int		row_offset;

	row_offset = -1;
	while (row_offset <= 1)
	{
		col_offset = -1;
		while (col_offset <= 1)
		{
			if (is_valid_cell(game, rows + row_offset, cols + col_offset))
			{
				if (!(game->map.coordinates[rows + row_offset]
						[cols + col_offset] == ' ')
					&& !(game->map.coordinates[rows + row_offset]
						[cols + col_offset] == '1')
					&& !(game->map.coordinates[rows + row_offset]
						[cols + col_offset] == '\0'))
					throw_error("Invalid map!", game);
			}
			col_offset++;
		}
		row_offset++;
	}
}

static void	check_edges(t_game *game, char cell)
{
	if (cell == ' ' || cell == '1')
		return ;
	else
		throw_error("Invalid map!", game);
}

static int	is_edge(t_game *game, int rows, int cols)
{
	if (rows == 0 || cols == 0
		|| rows == game->map.rows - 1 || cols == game->map.cols - 1)
		return (TRUE);
	return (FALSE);
}

static void	check_map_walls(t_game *game)
{
	int	rows;
	int	cols;

	rows = 0;
	while (rows < game->map.rows)
	{
		cols = 0;
		while (game->map.coordinates[rows][cols] && cols < game->map.cols)
		{
			if (is_edge(game, rows, cols))
				check_edges(game, game->map.coordinates[rows][cols]);
			if (game->map.coordinates[rows][cols] == ' ')
				check_surroundings(game, rows, cols);
			else if (ft_strchr("NSWE", game->map.coordinates[rows][cols]))
				save_player(game, rows, cols);
			else if (!ft_strchr("01", game->map.coordinates[rows][cols]))
				throw_error("Invalid character on map", game);
			cols++;
		}
		rows++;
	}
}

static void	save_map(t_game *game, char *map)
{
	int		fd;
	int		rows;
	char	*aux;

	fd = open_fd(map);
	while (get_next_line(fd, &aux) == 1 && !map_started(aux))
	{
		if (aux != NULL)
			free(aux);
	}
	if (aux != NULL)
	{
		game->map.coordinates[0] = ft_strdup(aux);
		free(aux);
	}
	rows = 1;
	while (get_next_line(fd, &game->map.coordinates[rows]) == 1)
		rows++;
	close(fd);
}

static void	count_map_size(t_game *game, char *map)
{
	int		fd;
	char	*aux;

	game->map.rows = 0;
	game->map.cols = 0;
	fd = open_fd(map);
	while (get_next_line(fd, &aux) == 1)
	{
		if (game->map.rows == 0 && !map_started(aux))
		{
			if (aux != NULL)
				free(aux);
			continue ;
		}
		if (ft_strlen(aux) == 0)
			game->error = TRUE;
		if (ft_strlen(aux) > game->map.cols)
			game->map.cols = ft_strlen(aux);
		game->map.rows++;
		if (aux != NULL)
			free(aux);
	}
	game->map.rows++;
	if (aux != NULL)
	{
		if (ft_strlen(aux) == 0)
			game->error = TRUE;
		free(aux);
	}
	close(fd);
}

static void	validate_player(t_game *game)
{
	int	rows;
	int	cols;
	int	has_player;

	has_player = 0;
	rows = 0;
	while (rows < game->map.rows)
	{
		cols = 0;
		while (cols < game->map.cols)
		{
			if (cols < ft_strlen(game->map.coordinates[rows]) && game->map.coordinates[rows][cols] && ft_strchr("NSWE",
				game->map.coordinates[rows][cols]))
				has_player++;
			cols++;
		}
		rows++;
	}
	if (!has_player)
		throw_error("No player was found!", game);
	if (has_player > 1)
		throw_error("You need to put exactly one player on the map.", game);
}

void	check_map(t_game *game, char *map)
{
	count_map_size(game, map);
	if (game->map.rows < 3 || game->map.cols < 3 || game->error)
		throw_error("Invalid map!", game);
	game->map.coordinates = ft_calloc(game->map.rows + 1, sizeof(char *));
	save_map(game, map);
	check_map_walls(game);
	validate_player(game);
	for (int i = 0; i < game->map.rows; i++)
		printf("'%s'\n", game->map.coordinates[i]);
	game->map.coordinates[(int)(game->player_pos.y)]
	[(int)(game->player_pos.x)] = '0';
	printf("player pos - [%f][%f]\n", game->player_pos.x, game->player_pos.y);
}

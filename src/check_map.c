/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarneir <acarneir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 19:47:13 by rfelipe-          #+#    #+#             */
/*   Updated: 2022/10/26 23:01:10 by acarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	save_player(t_game *game, int rows, int cols)
{
	game->player_pos = create_vector(rows + 0.5, cols + 0.5);
	game->player_dir = create_vector(0.0, -1.0);
	game->camera_plane = create_vector(0.66, 0.0);
	if (game->map.coordinates[rows][cols] == 'N')
	{
		game->player_dir = vector_rotation(game->player_dir, 0, 1);
		game->camera_plane = vector_rotation(game->camera_plane, 0, 1);
	}
	else if (game->map.coordinates[rows][cols] == 'S')
	{
		game->player_dir = vector_rotation(game->player_dir, M_PI, -1);
		game->camera_plane = vector_rotation(game->camera_plane, M_PI, -1);
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
	int		cols;

	rows = 0;
	fd = open_fd(map);
	while (rows <= game->temp_map.rows)
	{
		get_next_line(fd, &game->temp_map.coordinates[rows]);
		rows++;
	}
	close(fd);
	game->map.cols = game->temp_map.rows;
	game->map.rows = game->temp_map.cols;
	cols = 0;
	while (cols < game->temp_map.cols)
	{
		game->map.coordinates[cols] = ft_calloc(game->map.rows + 1, sizeof(char));
		cols++;
	}
	rows = 0;
	while (rows < game->temp_map.rows)
	{
		cols = 0;
		while (game->temp_map.coordinates[rows][cols] && cols < game->temp_map.cols)
		{
			printf("col = %d, row = %d\n", cols, rows);
			game->map.coordinates[cols][rows] = game->temp_map.coordinates[rows][cols];
			cols++;
		}
		rows++;
	}
}

static void	count_map_size(t_game *game, char *map)
{
	int		fd;
	char	*aux;

	game->temp_map.rows = 0;
	game->temp_map.cols = 0;
	fd = open_fd(map);
	while (get_next_line(fd, &aux) == 1)
	{
		if (ft_strlen(aux) > game->temp_map.cols)
			game->temp_map.cols = ft_strlen(aux);
		game->temp_map.rows++;
		if (aux != NULL)
			free(aux);
	}
	game->temp_map.rows++;
	if (aux != NULL)
		free(aux);
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
			if (game->map.coordinates[rows][cols] && ft_strchr("NSWE",
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
	if (game->temp_map.rows < 3 || game->temp_map.cols < 3)
		throw_error("Invalid map!", game);
	game->temp_map.coordinates = ft_calloc(game->temp_map.rows + 1, sizeof(char *));
	game->map.coordinates = ft_calloc(game->temp_map.cols + 1, sizeof(char *));
	save_map(game, map);
	check_map_walls(game);
	validate_player(game);
	game->map.coordinates[(int)(game->player_pos.x)]
	[(int)(game->player_pos.y)] = '0';
}

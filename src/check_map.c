/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfelipe- <rfelipe-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 19:47:13 by rfelipe-          #+#    #+#             */
/*   Updated: 2022/10/10 21:23:15 by rfelipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	check_map_characters2(char *aux, int *rows_n_cols, int *characters,
	t_game *game)
{
	if (aux[rows_n_cols[1]] == '0')
		characters[0]++;
	else if (aux[rows_n_cols[1]] == '1')
		characters[1]++;
	else if (aux[rows_n_cols[1]] == 'N' || aux[rows_n_cols[1]] == 'S'
		|| aux[rows_n_cols[1]] == 'E' || aux[rows_n_cols[1]] == 'W')
	{
		game->player_pos.x = rows_n_cols[0];
		game->player_pos.y = rows_n_cols[1];
		characters[2]++;
	}
	else
		throw_error("Invalid character on map");
}

static void	check_map_characters(t_game *game, int *characters)
{
	int		*rows_n_cols;

	rows_n_cols = ft_calloc(2, sizeof(int));
	while (rows_n_cols[0] < game->map.rows)
	{
		rows_n_cols[1] = 0;
		while (rows_n_cols[1] < game->map.cols)
		{
			check_map_characters2(game->map.coordinates[rows_n_cols[0]],
				rows_n_cols, characters, game);
			rows_n_cols[1]++;
		}
		rows_n_cols[0]++;
	}
	free(rows_n_cols);
}

static void	check_map_walls(t_game *game, char *map)
{
	int		fd;
	int		rows;
	int		cols;

	rows = 0;
	fd = open(ft_strjoin("./maps/", map), O_RDWR);
	while (rows < game->map.rows)
	{
		get_next_line(fd, &game->map.coordinates[rows]);
		cols = 0;
		while (cols < game->map.cols)
		{
			if ((cols == 0 || cols == game->map.cols - 1
					|| rows == 0 || rows == game->map.rows - 1)
				&& game->map.coordinates[rows][cols] != '1')
				throw_error("Map must be closed/surrounded by walls");
			cols++;
		}
		rows++;
	}
	close(fd);
}

static void	count_map_size(t_game *game, char *map)
{
	int		fd;
	char	*aux;

	game->map.rows = 0;
	game->map.cols = -1;
	fd = open(ft_strjoin("./maps/", map), O_RDWR);
	while (get_next_line(fd, &aux) == 1)
	{
		if (game->map.cols == -1)
			game->map.cols = (int) ft_strlen(aux);
		else if (game->map.cols != (int) ft_strlen(aux))
		{
			game->map.cols = -1;
			break ;
		}
		game->map.rows++;
	}
	if (game->map.cols != (int) ft_strlen(aux) && game->map.cols != -1)
		game->map.cols = -1;
	if (game->map.cols <= 0 || game->map.rows <= 0)
		throw_error("Map must be rectangular");
	game->map.rows++;
	if (aux != NULL)
		free(aux);
	close(fd);
}

void	check_map(t_game *game, char *map)
{
	int	*characters;

	characters = ft_calloc(3, sizeof(int));
	count_map_size(game, map);
	game->map.coordinates = malloc(sizeof(char *) * game->map.rows);
	check_map_walls(game, map);
	check_map_characters(game, characters);
	if (characters[2] == 0)
		throw_error("No player was found!");
	if (characters[2] != 1)
		throw_error("You need to put exactly one player on the map.");
	free(characters);
}
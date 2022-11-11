/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfelipe- <rfelipe-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 19:47:13 by rfelipe-          #+#    #+#             */
/*   Updated: 2022/11/11 18:12:18 by rfelipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	is_edge(t_game *game, int rows, int cols)
{
	if (rows == 0 || cols == 0 || rows == game->file.map.rows - 1
		|| cols == game->file.map.cols - 1)
		return (TRUE);
	return (FALSE);
}

static void	check_map_walls(t_game *game)
{
	int	rows;
	int	cols;

	rows = 0;
	while (rows < game->file.map.rows)
	{
		cols = 0;
		while (game->file.map.coordinates[rows][cols]
			&& cols < game->file.map.cols)
		{
			if (is_edge(game, rows, cols))
				check_edges(game, game->file.map.coordinates[rows][cols]);
			if (game->file.map.coordinates[rows][cols] == ' ')
				check_surroundings(game, rows, cols);
			else if (ft_strchr("NSWE", game->file.map.coordinates[rows][cols]))
				save_player(game, rows, cols);
			else if (!ft_strchr("01", game->file.map.coordinates[rows][cols]))
				throw_error("Invalid character on map", game);
			cols++;
		}
		rows++;
	}
}

static void	save_map(t_game *game, int fd)
{
	int		rows;
	char	*aux;

	while (get_next_line(fd, &aux) == 1 && !map_started(aux))
	{
		if (aux != NULL)
			free(aux);
	}
	if (aux != NULL)
	{
		game->file.map.coordinates[0] = ft_strdup(aux);
		free(aux);
	}
	rows = 1;
	while (get_next_line(fd, &game->file.map.coordinates[rows]) == 1)
		rows++;
}

static void	count_map_size(t_game *game, int fd)
{
	char	*aux;

	while (get_next_line(fd, &aux) == 1)
	{
		if (game->file.map.rows == 0 && !map_started(aux))
		{
			if (aux != NULL)
				free(aux);
			continue ;
		}
		if (ft_strlen(aux) == 0)
			game->error = TRUE;
		if (ft_strlen(aux) > game->file.map.cols)
			game->file.map.cols = ft_strlen(aux);
		game->file.map.rows++;
		if (aux != NULL)
			free(aux);
	}
	game->file.map.rows++;
	if (aux != NULL)
	{
		if (ft_strlen(aux) == 0)
			game->error = TRUE;
		free(aux);
	}
}

void	check_map(t_game *game, char *map)
{
	int	fd;

	fd = open_fd(map);
	count_map_size(game, fd);
	if (game->file.map.rows < 3 || game->file.map.cols < 3 || game->error)
	{
		close(fd);
		throw_error("Invalid map!", game);
	}
	game->file.map.coordinates = ft_calloc(
			game->file.map.rows + 1, sizeof(char *));
	save_map(game, fd);
	close(fd);
	check_map_walls(game);
	validate_player(game);
	game->file.map.coordinates[(int)(game->p.player_pos.y)]
	[(int)(game->p.player_pos.x)] = '0';
}

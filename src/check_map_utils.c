/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfelipe- <rfelipe-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 18:12:03 by rfelipe-          #+#    #+#             */
/*   Updated: 2022/11/11 18:12:33 by rfelipe-         ###   ########.fr       */
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

void	save_player(t_game *g, int rows, int cols)
{
	g->p.player_pos = create_vector(cols + 0.5, rows + 0.5);
	g->p.player_dir = create_vector(0.0, -1.0);
	g->dda.camera_plane = create_vector(0.66, 0.0);
	if (g->file.map.coordinates[rows][cols] == 'N')
	{
		g->p.player_dir = vector_rotation(g->p.player_dir, 0, 1);
		g->dda.camera_plane = vector_rotation(g->dda.camera_plane, 0, 1);
	}
	else if (g->file.map.coordinates[rows][cols] == 'S')
	{
		g->p.player_dir = vector_rotation(g->p.player_dir, M_PI, 1);
		g->dda.camera_plane = vector_rotation(g->dda.camera_plane, M_PI, 1);
	}
	else if (g->file.map.coordinates[rows][cols] == 'W')
	{
		g->p.player_dir = vector_rotation(g->p.player_dir, M_PI / 2, 1);
		g->dda.camera_plane = vector_rotation(g->dda.camera_plane, M_PI / 2, 1);
	}
	else if (g->file.map.coordinates[rows][cols] == 'E')
	{
		g->p.player_dir = vector_rotation(g->p.player_dir, M_PI / 2, -1);
		g->dda.camera_plane = vector_rotation(
				g->dda.camera_plane, M_PI / 2, -1);
	}
}

int	is_valid_cell(t_game *game, int rows, int cols)
{
	if (rows < 0 || rows > (game->file.map.rows - 1)
		|| cols < 0 || cols > (game->file.map.cols - 1))
		return (FALSE);
	return (TRUE);
}

void	check_surroundings(t_game *game, int rows, int cols)
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
				if (!(game->file.map.coordinates[rows + row_offset]
						[cols + col_offset] == ' ')
					&& !(game->file.map.coordinates[rows + row_offset]
						[cols + col_offset] == '1')
					&& !(game->file.map.coordinates[rows + row_offset]
						[cols + col_offset] == '\0'))
					throw_error("Invalid map!", game);
			}
			col_offset++;
		}
		row_offset++;
	}
}

void	check_edges(t_game *game, char cell)
{
	if (cell == ' ' || cell == '1')
		return ;
	else
		throw_error("Invalid map!", game);
}

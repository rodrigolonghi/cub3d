/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_params_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarneir <acarneir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 18:40:16 by rfelipe-          #+#    #+#             */
/*   Updated: 2022/11/11 22:09:52 by acarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	save_colors(t_game *g, char id, char *color)
{
	char	**matrix;

	if (ft_chrqty(color, ',') != 2)
	{
		g->error = TRUE;
		return ;
	}
	matrix = ft_split(color, ',');
	if (!ft_is_all_digit(matrix[0], ft_strlen(matrix[0]))
		|| !ft_is_all_digit(matrix[1], ft_strlen(matrix[1]))
		|| !ft_is_all_digit(matrix[2], ft_strlen(matrix[2])))
		g->error = TRUE;
	if (id == 'f' && g->file.floor.r == -1)
		g->file.floor = create_color(
				ft_atoi(matrix[0]), ft_atoi(matrix[1]), ft_atoi(matrix[2]));
	else if (id == 'f' && g->file.floor.r != -1)
		g->error = TRUE;
	else if (id == 'c' && g->file.ceilling.r == -1)
		g->file.ceilling = create_color(
				ft_atoi(matrix[0]), ft_atoi(matrix[1]), ft_atoi(matrix[2]));
	else if (id == 'c' && g->file.ceilling.r != -1)
		g->error = TRUE;
	ft_free_char_matrix(matrix);
}

void	save_e_w_texture(t_game *game, char id, char *path)
{
	if (id == 'e' && !game->error)
	{
		if (game->file.texture[2].addr == NULL)
			game->file.texture[2].addr = ft_strdup(path);
		else
			game->error = TRUE;
	}
	else if (id == 'w' && !game->error)
	{
		if (game->file.texture[3].addr == NULL)
			game->file.texture[3].addr = ft_strdup(path);
		else
			game->error = TRUE;
	}
}

void	save_n_s_texture(t_game *game, char id, char *path)
{
	if (id == 'n')
	{
		if (game->file.texture[0].addr == NULL)
			game->file.texture[0].addr = ft_strdup(path);
		else
			game->error = TRUE;
	}
	else if (id == 's' && !game->error)
	{
		if (game->file.texture[1].addr == NULL)
			game->file.texture[1].addr = ft_strdup(path);
		else
			game->error = TRUE;
	}
}

int	is_valid_end(t_game *game)
{
	if (game->file.texture[0].addr == NULL || game->file.texture[1].addr == NULL
		|| game->file.texture[2].addr == NULL
		|| game->file.texture[3].addr == NULL
		|| game->file.ceilling.r == -1 || game->file.floor.r == -1)
		return (FALSE);
	return (TRUE);
}

void	read_until_end(int fd)
{
	char	*aux;

	while (get_next_line(fd, &aux) == 1)
	{
		if (aux != NULL)
			ft_free_ptr((void *)&aux);
	}
	if (aux != NULL)
		ft_free_ptr((void *)&aux);
}

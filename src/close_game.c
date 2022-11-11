/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfelipe- <rfelipe-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 19:41:31 by rfelipe-          #+#    #+#             */
/*   Updated: 2022/11/11 18:43:33 by rfelipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	free_file(t_game *game)
{
	int	i;

	i = 0;
	if (game->file.texture != NULL)
	{
		while (i < 4)
		{
			if (game->file.texture[i].addr != NULL)
				ft_free_ptr((void *)&game->file.texture[i].addr);
			if (game->file.texture[i].img.ptr != NULL)
				mlx_destroy_image(game->mlx, game->file.texture[i].img.ptr);
			i++;
		}
		free(game->file.texture);
	}
	i = 0;
	if (game->file.map.coordinates)
	{
		while (i < game->file.map.rows)
		{
			free(game->file.map.coordinates[i]);
			i++;
		}
		free(game->file.map.coordinates);
	}
}

static void	free_game(t_game *game)
{
	if (game->mlx)
	{
		if (game->win)
		{
			mlx_destroy_window(game->mlx, game->win);
			game->win = NULL;
			ft_free_ptr((void *)&game->win);
		}
		mlx_destroy_display(game->mlx);
		ft_free_ptr(&game->mlx);
	}
	if (game)
		ft_free_ptr((void *)&game);
}

int	close_game(t_game *game)
{
	free_file(game);
	free_game(game);
	exit(0);
	return (0);
}

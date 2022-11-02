/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfelipe- <rfelipe-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 19:41:31 by rfelipe-          #+#    #+#             */
/*   Updated: 2022/10/31 21:42:28 by rfelipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	free_game(t_game *game)
{
	int	i;

	i = 0;
	// if (game->characters)
	// 	free(game->characters);
	if (game->map.coordinates)
	{
		while (i < game->map.rows)
		{
			free(game->map.coordinates[i]);
			i++;
		}
		free(game->map.coordinates);
	}
	if (game->mlx)
	{
		if (game->win)
		{
			mlx_destroy_window(game->mlx, game->win);
			game->win = NULL;
			ft_free_ptr((void *)&game->win);
		}
	// if (game->floor.img != NULL)
	// 	mlx_destroy_image(game->mlx, game->floor.img);
	// ft_free_ptr((void *)&game->player.pos);
	// ft_free_ptr((void *)&game->player.img);
		mlx_destroy_display(game->mlx);
		ft_free_ptr(&game->mlx);
	}
}

int	close_game(t_game *game)
{
	free_game(game);
	exit(0);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarneir <acarneir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 19:41:31 by rfelipe-          #+#    #+#             */
/*   Updated: 2022/11/10 22:31:18 by acarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	free_game(t_game *game)
{
	int	i;

	i = 0;
	// if (game->characters)
	// 	free(game->characters);
	if (game->texture != NULL)
	{
		while (i < 4)
		{
			if (game->texture[i].addr != NULL)
				ft_free_ptr((void *)&game->texture[i].addr);
			if (game->texture[i].img.ptr != NULL)
				mlx_destroy_image(game->mlx, game->texture[i].img.ptr);
			i++;
		}
		free(game->texture);
	}
	i = 0;
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

	if(game)
		ft_free_ptr((void *)&game);
}

int	close_game(t_game *game)
{
	free_game(game);
	exit(0);
	return (0);
}

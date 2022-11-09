/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarneir <acarneir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 19:41:31 by rfelipe-          #+#    #+#             */
/*   Updated: 2022/11/08 20:22:01 by acarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	free_game(t_game *game)
{
	int	i;

	i = 0;
	// if (game->characters)
	// 	free(game->characters);
	if (game->no.addr != NULL)
		free(game->no.addr);
	if (game->so.addr != NULL)
		free(game->so.addr);
	if (game->ea.addr != NULL)
		free(game->ea.addr);
	if (game->we.addr != NULL)
		free(game->we.addr);
	if (game->no.img.ptr != NULL)
		mlx_destroy_image(game->mlx, game->no.img.ptr);
	if (game->so.img.ptr != NULL)
		mlx_destroy_image(game->mlx, game->so.img.ptr);
	if (game->ea.img.ptr != NULL)
		mlx_destroy_image(game->mlx, game->ea.img.ptr);
	if (game->we.img.ptr != NULL)
		mlx_destroy_image(game->mlx, game->we.img.ptr);
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

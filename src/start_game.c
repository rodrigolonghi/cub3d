/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarneir <acarneir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 19:34:40 by rfelipe-          #+#    #+#             */
/*   Updated: 2022/11/10 23:08:41 by acarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	game_loop(t_game *game)
{
	refresh_player(game);
	calculate(game);
	render(game);
	return (0);
}

static void	initiate(t_game *game)
{
	game->mlx = NULL;
	game->win = NULL;
	game->error = FALSE;
	game->movement_speed = 1.0 / 60.0;
	game->rotation_speed = 1.0 / 60.0;
	game->rotation = 0;
	game->x_walk = 0.0;
	game->y_walk = 0.0;
	game->dist_wall = 0.0;
	game->texture = malloc(4 * sizeof(t_texture));
	game->texture[0].addr = NULL;
	game->texture[1].addr = NULL;
	game->texture[2].addr = NULL;
	game->texture[3].addr = NULL;
	game->texture[0].img.ptr = NULL;
	game->texture[1].img.ptr = NULL;
	game->texture[2].img.ptr = NULL;
	game->texture[3].img.ptr = NULL;
	game->map.coordinates = NULL;
	game->ceilling.r = -1;
	game->floor.r = -1;
}

void	start_game(t_game *game, int argc, char *argv[])
{
	initiate(game);
	game->mlx = mlx_init();
	check_params(game, argc, argv);
	check_map(game, argv[1]);
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cub3D");
	mlx_hook(game->win, 2, 1L << 0, press, game);
	mlx_hook(game->win, 3, 1L << 1, release, game);
	mlx_hook(game->win, 17, 0, close_game, game);
	mlx_loop_hook(game->mlx, &game_loop, game);
	mlx_loop(game->mlx);
}

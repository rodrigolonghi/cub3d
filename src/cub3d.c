/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfelipe- <rfelipe-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 20:03:38 by rfelipe-          #+#    #+#             */
/*   Updated: 2022/10/12 15:41:37 by rfelipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	temp_initiate_vars(t_game *game)
{
	game->ceilling = create_color(190, 190, 255);
	game->floor = create_color(130, 130, 130);
}

int	main(int argc, char *argv[])
{
	t_game	game;

	temp_initiate_vars(&game);
	start_game(&game, argc, argv);
	return (0);
}

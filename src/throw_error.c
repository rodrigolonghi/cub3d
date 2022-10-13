/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   throw_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarneir <acarneir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 19:45:35 by rfelipe-          #+#    #+#             */
/*   Updated: 2022/10/12 21:37:47 by acarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	throw_error(char *e, t_game *game)
{
	printf("Error\n%s\n", e);
	if (game)
		close_game(game);
	else
		exit(0);
}

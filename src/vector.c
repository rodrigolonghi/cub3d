/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfelipe- <rfelipe-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 21:54:53 by acarneir          #+#    #+#             */
/*   Updated: 2022/10/19 21:47:56 by rfelipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_vec	vector_mul(t_vec a, t_vec b)
{
	t_vec	vec;

	vec.x = a.x * b.x;
	vec.y = a.y * b.y;
	return (vec);
}

t_vec	vector_rotation(t_vec vec, double degree, int rotation)
{
	t_vec	new_vec;

	if (rotation == 1)
		new_vec = create_vector(cos(degree) * vec.x + sin(degree) * vec.y,
				-1 * sin(degree) * vec.x + cos(degree) * vec.y);
	else if (rotation == -1)
		new_vec = create_vector(cos(degree) * vec.x + -1 * sin(degree) * vec.y,
				sin(degree) * vec.x + cos(degree) * vec.y);
	else
		new_vec = vec;
	return (new_vec);
}

t_vec	vector_add(t_vec a, t_vec b)
{
	t_vec	vec;

	vec.x = a.x + b.x;
	vec.y = a.y + b.y;
	return (vec);
}

t_vec	vector_mul_scal(t_vec a, double b)
{
	t_vec	vec;

	vec.x = b * a.x;
	vec.y = b * a.y;
	return (vec);
}

t_vec	create_vector(double x, double y)
{
	t_vec	vec;

	vec.x = x;
	vec.y = y;
	return (vec);
}

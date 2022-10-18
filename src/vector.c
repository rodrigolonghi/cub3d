/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfelipe- <rfelipe-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 21:54:53 by acarneir          #+#    #+#             */
/*   Updated: 2022/10/17 22:07:44 by rfelipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// double	vector_length(t_vec a)
// {
// 	double	length;

// 	length = a.x * a.x + a.y * a.y + a.z * a.z + a.w * a.w;
// 	length = sqrt(length);
// 	return (length);
// }

// t_vec	vector_div(t_vec a, double b)
// {
// 	t_vec	vec;

// 	vec.x = a.x / b;
// 	vec.y = a.y / b;
// 	vec.z = a.z / b;
// 	vec.w = a.w / b;
// 	return (vec);
// }

// t_vec	vector_sub(t_vec a, t_vec b)
// {
// 	t_vec	vec;

// 	vec.x = a.x - b.x;
// 	vec.y = a.y - b.y;
// 	vec.z = a.z - b.z;
// 	vec.w = a.w - b.w;
// 	return (vec);
// }

t_vec	vector_rotation(t_vec vec, double degree, int wise)
{
	t_vec	new_vec;

	if (wise == 1)
		new_vec = create_vector(cos(degree) * vec.x + sin(degree) * vec.y,
				-1 * sin(degree) * vec.x + cos(degree) * vec.y);
	else if (wise == -1)
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

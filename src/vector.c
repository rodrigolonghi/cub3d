/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarneir <acarneir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 21:54:53 by acarneir          #+#    #+#             */
/*   Updated: 2022/10/14 22:38:56 by acarneir         ###   ########.fr       */
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

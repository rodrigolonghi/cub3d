/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itohex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfelipe- <rfelipe-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 04:23:43 by rfelipe-          #+#    #+#             */
/*   Updated: 2022/08/17 04:37:51 by rfelipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static char	*reverse_nbr(char *nbr)
{
	int		col;
	char	*reverse;

	col = 0;
	reverse = ft_calloc(9, sizeof(char));
	reverse[0] = '0';
	reverse[1] = 'x';
	while (col < 6)
	{
		reverse[col + 2] = nbr[5 - col];
		col++;
	}
	free(nbr);
	return (reverse);
}

char	*ft_itohex(unsigned int arg)
{
	char	*hexadecimal_table;
	int		col;
	char	*nbr;

	col = 5;
	hexadecimal_table = "0123456789ABCDEF";
	nbr = ft_calloc(7, sizeof(char));
	if (arg == 0)
		nbr[0] = '0';
	else
	{
		while (arg != 0 && col >= 0)
		{
			nbr[col] = hexadecimal_table[arg % 16];
			arg /= 16;
			col--;
		}
	}
	return (reverse_nbr(nbr));
}

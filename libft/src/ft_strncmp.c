/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfelipe- <rfelipe-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 05:54:33 by rfelipe-          #+#    #+#             */
/*   Updated: 2022/10/10 21:21:37 by rfelipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	size_t	pos;

	pos = 0;
	while (pos < n)
	{
		if (s1[pos] != s2[pos])
			return ((unsigned char)s1[pos] - (unsigned char)s2[pos]);
		else if (s1[pos] == '\0' || s2[pos] == '\0')
			return ((unsigned char)s1[pos] - (unsigned char)s2[pos]);
		pos++;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amimouni <amimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 00:03:38 by atouati           #+#    #+#             */
/*   Updated: 2022/11/18 08:39:16 by amimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell2.h"

char	*ft_strcpy(char *dst, const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		dst[i] = str[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

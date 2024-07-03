/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amimouni <amimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 03:48:25 by atouati           #+#    #+#             */
/*   Updated: 2022/11/25 23:21:55 by amimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell2.h"

char	**replace_in_quotes(char **str, char a, char b)
{
	int	i;

	i = 0;
	while (str[i])
	{
		str[i] = handling_quotes(str[i], a, b);
		i++;
	}
	return (str);
}

int	cont_quot(char *str)
{
	int	i;
	int	c;

	c = 0;
	i = 0;
	while (str[i])
	{
		c += cont_dif_puot(str, &i);
		if (str[i] == '\0')
			break ;
		i++;
	}
	return (c);
}

char	*remove_quotes(char *str)
{
	int		i;
	char	*dest;
	int		j;

	i = ft_strlen(str) - (cont_quot(str) * 2);
	dest = malloc(sizeof(char) * i + 1);
	if (!dest)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		copy_without_quot(str, dest, &i, &j);
		if (str[i] == '\0')
			break ;
		i++;
	}
	dest[j] = '\0';
	free(str);
	return (dest);
}

int	check_quot(char *str)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '"')
			return (D_QUOTES);
		if (str[i] == '\'')
			return (S_QUOTES);
		i++;
	}
	return (NO_QUOTES);
}

int	quot_cont(char *str, int n, char sep)
{
	int	i;
	int	c;

	c = 0;
	i = 0;
	while (i <= n)
	{
		if (str[i] == sep)
			c++;
		i++;
	}
	if ((c % 2) == 0)
		return (1);
	return (0);
}

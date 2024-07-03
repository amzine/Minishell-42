/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atouati <atouati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 22:34:43 by atouati           #+#    #+#             */
/*   Updated: 2022/11/23 07:46:31 by atouati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell2.h"

char	*copy(t_token *ptr, char *str, char *dest, char *tmp)
{
	ptr->j = 0;
	count_for_alloc(str, ptr);
	dest = malloc(sizeof(char) * ptr->j + 1);
	ptr->j = 0;
	while (str[ptr->n] != '\0' && str[ptr->n] != '"' && str[ptr->n] != '\'')
	{
		dest[ptr->j] = str[ptr->n];
		ptr->j++;
		ptr->n++;
	}
	dest[ptr->j] = '\0';
	tmp = ft_strrjoin(tmp, dest);
	return (tmp);
}

int	check_error(char	**str)
{
	int	i;

	i = 0;
	while (str[i] && str[i + 1])
	{
		if ((str[i][0] == '<' || str[i][0] == '>')
			&& (str[i + 1][0] == '<' || str[i + 1][0] == '>'))
			return (0);
		if (str[i][0] == '<' && str[i][1] == '>')
			return (0);
		if (str[i][0] == '>' && str[i][1] == '<')
			return (0);
		i++;
	}
	if (str[i + 1] == NULL && (str[i][0] == '<' || str[i][0] == '>'))
		return (0);
	return (1);
}

int	check_error_2(char *str)
{
	if (str[0] == '<' && str[1] == '<')
	{
		if (!ft_memcmp(str, "<<"))
			return (0);
	}
	else if (str[0] == '>' && str[1] == '>')
	{
		if (!ft_memcmp(str, ">>"))
			return (0);
	}
	else if (str[0] == '<' && str[1] == '\0')
	{
		return (0);
	}
	else if (str[0] == '>' && str[1] == '\0')
	{
		return (0);
	}
	else
		return (0);
	return (1);
}

void	add_quots(char *dest, char *str, int *i, int *j)
{
	if (str[*i] == '\"')
	{
		dest[(*j)++] = str[(*i)++];
		while (str[*i] != '\"' && str[*i])
			dest[(*j)++] = str[(*i)++];
	}
	if (str[*i] == '\'')
	{
		dest[(*j)++] = str[(*i)++];
		while (str[*i] != '\'' && str[*i])
			dest[(*j)++] = str[(*i)++];
	}
}

char	*handling_tab(char *str)
{
	int		i;
	int		j;
	char	*dest;

	i = 0;
	j = 0;
	dest = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!dest)
		return (NULL);
	while (str[i])
	{
		add_quots(dest, str, &i, &j);
		if (str[i] == '\0')
			break ;
		if (replace_tab(str, dest, &i, &j))
			continue ;
		dest[j] = str[i];
		j++;
		i++;
	}
	dest[j] = '\0';
	free(str);
	return (dest);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atouati <atouati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 06:42:13 by atouati           #+#    #+#             */
/*   Updated: 2022/11/23 07:35:12 by atouati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell2.h"

void	copy_without_quot(char *str, char *dest, int *i, int *j)
{
	if (str[*i] == '"')
	{
		(*i)++;
		while (str[*i] != '"' && str[*i])
		{
			dest[*j] = str[*i];
			(*i)++;
			(*j)++;
		}
	}
	else if (str[*i] == '\'')
	{
		(*i)++;
		while (str[*i] != '\'' && str[*i])
		{
			dest[*j] = str[*i];
			(*i)++;
			(*j)++;
		}
	}
	else if (str[*i] != '\0')
	{
		dest[*j] = str[*i];
		(*j)++;
	}
}

int	cont_dif_puot(char *str, int *i)
{
	int	c;

	c = 0;
	if (str[*i] == '"')
	{
		(*i)++;
		while (str[*i] != '"' && str[*i])
			(*i)++;
		c++;
	}
	else if (str[*i] == '\'')
	{
		(*i)++;
		while (str[*i] != '\'' && str[*i])
			(*i)++;
		c++;
	}
	return (c);
}

int	error_unexpected(char **str, int i, int n, t_shell *mini)
{
	if (n == 0)
	{
		if (!check_error(str))
		{
			printf("minishell: syntax error near unexpected token\n");
			mini->ret = 258;
			return (0);
		}
	}
	if (n == 1)
	{
		if (check_error_2(str[i]))
		{
			printf("minishell: syntax error near unexpected token\n");
			mini->ret = 258;
			return (0);
		}
	}
	return (1);
}

char	*handling_and_expanding(char **str, int i, char **env, t_shell *mini)
{
	str[i] = handling_quotes(str[i], -1, ' ');
	str[i] = check_expand(str[i], env, get_type(i, str), mini);
	return (str[i]);
}

void	init_tmp(t_minishell *tmp, char **str, int i)
{
	tmp->data = ft_strdup(str[i]);
	tmp->type = get_type(i, str);
	tmp->next = NULL;
}

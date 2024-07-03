/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amimouni <amimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 05:48:33 by amimouni          #+#    #+#             */
/*   Updated: 2022/11/26 09:56:23 by amimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell2.h"

t_minishell	**fill_token(t_token *ptr, char **env, t_shell *mini)
{
	t_minishell	*head;
	t_minishell	**tokens;
	int			i;

	tokens = sep_split(ptr->pip_split, ' ', env, mini);
	i = 0;
	while (tokens[i] != NULL)
	{
		head = tokens[i];
		while (tokens[i] != NULL)
		{
			tokens[i]->quotes = check_quot(tokens[i]->data);
			tokens[i]->data = remove_quotes(tokens[i]->data);
			tokens[i] = tokens[i]->next;
		}
		tokens[i] = head;
		i++;
	}
	return (tokens);
}

int	skeep_space(char *parse_line)
{
	int	i;

	i = 0;
	while (parse_line[i] && parse_line[i] == ' ')
		i++;
	return (i);
}

int	check_error_op(char *parse_line)
{
	int	i;

	i = 0;
	while (parse_line[i])
	{
		if (parse_line[i] == '|'
			&& parse_line[i + skeep_space(parse_line + i + 1) + 1] == '\0')
			return (0);
		if (parse_line[i] == '|'
			&& parse_line[i + skeep_space(parse_line + i + 1) + 1] == '|')
			return (0);
		i++;
	}
	return (1);
}

t_minishell	**split_and_fill(t_token *ptr, char **env, t_shell *mini)
{
	int			i;
	t_minishell	**tokens;

	i = 0;
	i = skeep_space(ptr->parse_line);
	if (ptr->parse_line[i] == '|')
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		mini->ret = 258;
		ptr->if_true = 1;
		return (0);
	}
	if (!check_error_op(ptr->parse_line))
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		mini->ret = 258;
		ptr->if_true = 1;
		return (0);
	}
	ptr->pip_split = ft_split(ptr->parse_line + i, '|');
	free(ptr->parse_line);
	ptr->pip_split = replace_in_quotes(ptr->pip_split, -1, '|');
	ptr->pip_split = replace_in_quotes(ptr->pip_split, ' ', -1);
	tokens = fill_token(ptr, env, mini);
	return (tokens);
}

t_minishell	**parser(t_token *ptr, char **env, t_shell *mini)
{
	t_minishell	**tokens;

	ptr->parse_line = handling_tab(ptr->parse_line);
	ptr->parse_line = handling_spaces(ptr->parse_line);
	ptr->parse_line = handling_quotes(ptr->parse_line, '|', -1);
	if (!ptr->parse_line)
	{
		printf("quot error\n");
		ptr->if_true = 1;
		return (0);
	}
	tokens = split_and_fill(ptr, env, mini);
	return (tokens);
}

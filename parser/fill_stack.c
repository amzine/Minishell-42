/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_stack.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amimouni <amimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 03:46:24 by atouati           #+#    #+#             */
/*   Updated: 2022/11/26 01:53:46 by amimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell2.h"

void	add_num(t_minishell **top, t_minishell *tmp)
{
	t_minishell	*temp;

	if (*top == NULL)
		*top = tmp;
	else
	{
		temp = *top;
		while (temp->next)
			temp = temp->next;
		temp->next = tmp;
	}
}

int	get_type(int i, char **str)
{
	if (i == 0)
		return (ARG);
	else if (str[i - 1][0] == '<' && str[i - 1][1] == '\0')
		return (INPUT_FILE);
	else if (str[i - 1][0] == '>' && str[i - 1][1] == '\0')
		return (OUTPUT_FILE);
	else if (str[i - 1][0] == '>' && str[i - 1][1] == '>')
		return (APPEND);
	else if (str[i - 1][0] == '<' && str[i - 1][1] == '<')
		return (HEREDOC);
	else
		return (ARG);
}

t_minishell	*fill_stack(t_minishell *stack, char **str
				, char **env, t_shell *mini)
{
	t_minishell	*tmp;
	int			i;

	i = 0;
	tmp = NULL;
	if (!error_unexpected(str, i, 0, mini))
		return (NULL);
	while (str[i])
	{
		if (!error_unexpected(str, i, 1, mini))
			return (NULL);
		if (str[i][0] != '<' && str[i][0] != '>' && str[i][0] != '|')
		{
			str[i] = handling_and_expanding(str, i, env, mini);
			if (str[i][0] != '\0')
			{
				tmp = malloc(sizeof(t_minishell));
				init_tmp(tmp, str, i);
				add_num(&stack, tmp);
			}
		}
		i++;
	}
	return (stack);
}

void	define_cmd(t_minishell **tokens)
{
	int			i;
	t_minishell	*head;

	i = 0;
	while (tokens[i])
	{
		head = tokens[i];
		while (tokens[i])
		{
			if (tokens[i]->type == ARG)
			{
				tokens[i]->type = CMD;
				break ;
			}
			tokens[i] = tokens[i]->next;
		}
		tokens[i] = head;
		i++;
	}
}

t_minishell	**sep_split(char **str, char sep, char **env, t_shell *mini)
{
	t_minishell	**tokens;
	int			i;
	char		**chr;

	i = 0;
	while (str[i])
		i++;
	tokens = malloc(sizeof(t_minishell *) * (i + 1));
	i = 0;
	while (str[i])
	{
		chr = ft_split(str[i], sep);
		tokens[i] = NULL;
		tokens[i] = fill_stack(tokens[i], chr, env, mini);
		i++;
		ft_free(chr);
	}
	tokens[i] = NULL;
	define_cmd(tokens);
	ft_free(str);
	return (tokens);
}

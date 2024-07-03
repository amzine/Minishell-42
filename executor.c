/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amimouni <amimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 22:18:12 by amimouni          #+#    #+#             */
/*   Updated: 2022/11/29 16:57:19 by amimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell2.h"

static int	is_type(t_minishell *token, int type)
{
	if (token && token->type == type)
		return (1);
	else
		return (0);
}

void	count_heredoc(t_shell *ptr, t_minishell **token)
{
	int			i;
	t_minishell	*head;

	i = 0;
	while (token[i])
	{
		head = token[i];
		while (token[i])
		{
			if (is_type(token[i], HEREDOC))
				ptr->n++;
			token[i] = token[i]->next;
		}
		token[i] = head;
		i++;
	}
}

void	redir_and_exec(t_shell *mini, t_minishell *token)
{
	t_minishell	*head;

	head = token;
	while (token)
	{
		if (is_type(token, OUTPUT_FILE))
			redir(mini, token, OUTPUT_FILE);
		else if (is_type(token, APPEND))
			redir(mini, token, APPEND);
		else if (is_type(token, INPUT_FILE))
			input(mini, token);
		else if (is_type(token, HEREDOC))
		{
			mini->n--;
			if (mini->n == 0)
				dup2(mini->pip[mini->tmp_fd], STDIN_FILENO);
			mini->tmp_fd++;
		}
		if (g_sig.flag == 1)
			return ;
		token = token->next;
	}
	token = head;
	if (mini->no_exec == 0)
		exec_cmd(mini, token);
}

void	open_all_heredoc(t_shell *ptr, t_minishell **token)
{
	int			i;
	t_minishell	*head;

	i = 0;
	ptr->n = 0;
	count_heredoc(ptr, token);
	ptr->tmp_fd = 0;
	ptr->pip = malloc(sizeof(int) * ptr->n);
	while (token[i])
	{
		head = token[i];
		while (token[i])
		{
			if (is_type(token[i], HEREDOC))
			{
				if (g_sig.hereflag != 0)
					break ;
				heredoc_func(ptr, token[i]);
				ptr->tmp_fd++;
			}
			token[i] = token[i]->next;
		}
		token[i] = head;
		i++;
	}
}

void	execution(t_shell *ptr)
{
	int			status;
	int			i;

	i = 0;
	open_all_heredoc(ptr, ptr->start);
	ptr->tmp_fd = 0;
	while (ptr->start[i])
	{
		if (ptr->start[i + 1])
			minipipe(ptr, ptr->start[i]);
		else
		{
			redir_and_exec(ptr, ptr->start[i]);
			reset_std(ptr);
			close_fds(ptr);
			reset_fds(ptr);
		}
		ptr->no_exec = 0;
		i++;
	}
	while (i--)
		waitpid(-1, &status, 0);
	free(ptr->pip);
}

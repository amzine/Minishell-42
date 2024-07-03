/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amimouni <amimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 18:58:29 by amimouni          #+#    #+#             */
/*   Updated: 2022/11/29 16:11:19 by amimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell2.h"

void	redir(t_shell *mini, t_minishell *token, int type)
{
	ft_close(mini->fdout);
	if (type == OUTPUT_FILE)
		mini->fdout = open(token->data, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	else
		mini->fdout = open(token->data, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
	if (access(token->data, F_OK) == -1)
	{
		ft_putstr_fd("minishell: ", STDERR);
		ft_putstr_fd(token->data, STDERR);
		ft_putstr_fd(": No such file or directory\n", STDERR);
		mini->ret = 1;
		mini->no_exec = 1;
		return ;
	}
	else if (access(token->data, (R_OK | W_OK)) == -1)
	{
		ft_putstr_fd("minishell: ", STDERR);
		ft_putstr_fd(token->data, STDERR);
		ft_putstr_fd(": permission denied\n", STDERR);
		mini->no_exec = 1;
		mini->ret = 1;
		return ;
	}
	dup2(mini->fdout, STDOUT);
}

void	input(t_shell *mini, t_minishell *token)
{
	ft_close(mini->fdin);
	mini->fdin = open(token->data, O_RDONLY, S_IRWXU);
	if (access(token->data, F_OK) == -1)
	{
		ft_putstr_fd("minishell: ", STDERR);
		ft_putstr_fd(token->data, STDERR);
		ft_putstr_fd(": No such file or directory\n", STDERR);
		mini->ret = 1;
		mini->no_exec = 1;
		return ;
	}
	if (access(token->data, R_OK) == -1)
	{
		ft_putstr_fd("minishell: ", STDERR);
		ft_putstr_fd(token->data, STDERR);
		ft_putstr_fd(": permission denied\n", STDERR);
		mini->no_exec = 1;
		mini->ret = 1;
		return ;
	}
	dup2(mini->fdin, STDIN);
}

void	decrement(t_minishell *token, t_shell *mini)
{
	while (token)
	{
		if (token->type == HEREDOC)
			mini->n--;
		token = token->next;
	}
}

void	minipipe(t_shell *mini, t_minishell *token)
{
	pid_t	pid;
	int		pipefd[2];

	pipe(pipefd);
	pid = fork();
	if (pid == 0)
	{
		ft_close(pipefd[0]);
		dup2(pipefd[1], STDOUT);
		close(pipefd[1]);
		mini->pipout = pipefd[1];
		mini->no_exec = 0;
		redir_and_exec(mini, token);
		exit(0);
	}
	else
	{
		ft_close(pipefd[1]);
		dup2(pipefd[0], STDIN);
		close(pipefd[0]);
		mini->pipin = pipefd[0];
		mini->pid = pid;
		decrement(token, mini);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amimouni <amimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 01:50:54 by amimouni          #+#    #+#             */
/*   Updated: 2022/11/25 00:08:14 by amimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell2.h"

int	is_builtin(char *command)
{
	if (ft_strcmp(command, "echo") == 0)
		return (1);
	if (ft_strcmp(command, "cd") == 0)
		return (1);
	if (ft_strcmp(command, "pwd") == 0)
		return (1);
	if (ft_strcmp(command, "env") == 0)
		return (1);
	if (ft_strcmp(command, "export") == 0)
		return (1);
	if (ft_strcmp(command, "unset") == 0)
		return (1);
	if (ft_strcmp(command, "PWD") == 0)
		return (1);
	return (0);
}

static	void	fill_token(t_minishell *token, char **tabs)
{
	int	i;

	i = 0;
	while (token)
	{
		if (token->type == CMD)
			tabs[i++] = ft_strdup(token->data);
		if (token->type == ARG)
			tabs[i++] = ft_strdup(token->data);
		token = token->next;
	}
	tabs[i] = NULL;
}

char	**cmd_tab(t_minishell *start)
{
	t_minishell	*token;
	char		**tabs;
	int			i;

	if (!start)
		return (NULL);
	token = start;
	i = 2;
	while (token)
	{
		if (token->type == ARG)
			i++;
		token = token->next;
	}
	tabs = malloc(sizeof(char *) * i);
	if (!(tabs))
		return (NULL);
	i = 0;
	token = start;
	fill_token(token, tabs);
	return (tabs);
}

void	exec_cmd(t_shell *mini, t_minishell *token)
{
	char	**cmd;
	int		i;

	cmd = cmd_tab(token);
	i = 0;
	if (cmd && ft_strcmp(cmd[0], "exit") == 0)
		run_exit(cmd, mini);
	else if (cmd && is_builtin(cmd[0]))
		mini->ret = run_builtins(cmd, mini);
	else if (cmd[0])
		mini->ret = run_bin(cmd, mini->env, mini);
	free_tab(cmd);
	ft_close(mini->pipout);
	ft_close(mini->pipin);
	mini->pipin = -1;
	mini->pipout = -1;
	mini->charge = 0;
}

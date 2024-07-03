/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amimouni <amimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 02:54:17 by amimouni          #+#    #+#             */
/*   Updated: 2022/11/29 16:41:22 by amimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell2.h"

static int	create_temporary_file(void)
{
	return (open("../.tmp_hdocu", O_WRONLY | O_CREAT | O_TRUNC, 0600));
}

void	restores_stdin_and_closes(t_shell *ptr)
{
	ptr->pip[ptr->tmp_fd] = open("../.tmp_hdocu", O_RDONLY);
	unlink(".tmp_hdocu");
}

void	interrupt_here_doc(int signal)
{
	g_sig.hereflag = 1;
	(void)signal;
	exit(1);
}

static void	get_and_write_input(t_shell *head, t_minishell *token, int tmp_fd)
{
	char	*input;
	char	**env;

	env = put_in_tab(head);
	signal(SIGINT, interrupt_here_doc);
	while (1)
	{
		input = readline("> ");
		if (!input)
			exit(errno);
		if (ft_strncmp(input, token->data, ft_strlen(input) + 1))
		{
			input = check_expand(input, env, ARG, head);
			ft_putendl_fd(input, tmp_fd);
		}
		else
		{
			close(tmp_fd);
			free(input);
			break ;
		}
		free(input);
	}
	free(env);
	exit(0);
}

void	heredoc_func(t_shell *head, t_minishell *token)
{
	int	tmp_fd;
	int	pid;
	int	status;

	tmp_fd = create_temporary_file();
	head->here_in = dup(STDIN_FILENO);
	if (tmp_fd == -1)
		return ;
	pid = fork();
	if (pid == 0)
	{
		get_and_write_input(head, token, tmp_fd);
		close(tmp_fd);
	}
	waitpid(pid, &status, 0);
	if (status != 0)
		g_sig.hereflag = 1;
	head->ret = WEXITSTATUS(status);
	restores_stdin_and_closes(head);
	close(tmp_fd);
}

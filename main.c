/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atouati <atouati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 05:55:50 by amimouni          #+#    #+#             */
/*   Updated: 2022/11/29 22:10:39 by atouati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell2.h"

void	minishell(t_shell *mini, t_token *ptr, char **enva)
{
	if (ptr->parse_line[0] == '\0')
	{
		free(ptr->parse_line);
		return ;
	}
	mini->start = parser(ptr, enva, mini);
	if (ptr->if_true == 1)
	{
		free(ptr->parse_line);
		return ;
	}
	execution(mini);
	free_token(mini);
}

char	**more_stuff(t_shell *mini, t_token *ptr, char **enva)
{
	g_sig.flag = 0;
	mini->exit = 0;
	ptr->if_true = 0;
	enva = put_in_tab(mini);
	init_sig();
	return (enva);
}

void	init_mini(t_shell *t_mini, char **env)
{
	init_shell(t_mini);
	reset_fds(t_mini);
	init_env(t_mini, env);
	init_export_env(t_mini, env);
}

void	signals(void)
{
	signal(SIGINT, &sig_handler);
	signal(SIGQUIT, SIG_IGN);
}

int	main(int ac, char **av, char **env)
{
	t_shell	t_mini;
	t_token	ptr;
	char	**enva;

	enva = NULL;
	init_mini(&t_mini, env);
	(void)ac;
	(void)av;
	while (1)
	{
		g_sig.hereflag = 0;
		enva = more_stuff(&t_mini, &ptr, enva);
		signals();
		ptr.parse_line = readline("Minishell-$ ");
		if (!ptr.parse_line)
		{
			ft_putstr_fd("exit\n", 1);
			exit(0);
		}
		if (ptr.parse_line[0] != '\0')
			add_history(ptr.parse_line);
		minishell(&t_mini, &ptr, enva);
		ft_free(enva);
	}
}

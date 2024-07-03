/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amimouni <amimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 04:30:44 by amimouni          #+#    #+#             */
/*   Updated: 2022/11/26 02:26:19 by amimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell2.h"

int	execute_cmd(char *path, char **av, t_list_env *env, t_shell *mini)
{
	int		ret;

	(void)mini;
	ret = 0;
	signal_for_blocking_cmd();
	g_sig.pid = fork();
	if (g_sig.pid == 0)
		ret = exev(path, av, env);
	else
	{
		waitpid(g_sig.pid, &ret, 0);
		ret = WEXITSTATUS(ret);
		signals();
	}
	if (g_sig.sigint == 1 || g_sig.sigquit == 1)
		return (g_sig.exit_status);
	return (ret);
}

char	*join_path(char *s1, char *s2)
{
	char	*tmp;
	char	*path;

	tmp = ft_strjoin(s1, "/");
	path = ft_strjoin(tmp, s2);
	free(tmp);
	return (path);
}

char	*check_dir(char *bin, char *command)
{
	DIR				*folder;
	struct dirent	*entry;
	char			*path;

	path = NULL;
	folder = opendir(bin);
	if (!folder)
		return (NULL);
	entry = readdir(folder);
	while (entry)
	{
		if (ft_strcmp(entry->d_name, command) == 0)
			path = join_path(bin, entry->d_name);
		entry = readdir(folder);
	}
	closedir(folder);
	return (path);
}

int	run_bin(char **av, t_list_env *env, t_shell *mini)
{
	int		i;
	char	**bin;
	char	*path;
	int		ret;

	ret = 127;
	i = 0;
	while (env && env->value && ft_strncmp(env->value, "PATH=", 5) != 0)
		env = env->next;
	if (env == NULL || env->next == NULL)
		return (execute_cmd(av[0], av, env, mini));
	bin = ft_split(env->value, ':');
	if (!av[0] && !bin[0])
		return (1);
	i = 1;
	path = check_dir(bin[0] + 5, av[0]);
	while (av[0] && bin[i] && path == NULL)
		path = check_dir(bin[i++], av[0]);
	if (path != NULL)
		ret = execute_cmd(path, av, env, mini);
	else
		ret = execute_cmd(av[0], av, env, mini);
	free_tab(bin);
	free(path);
	return (ret);
}

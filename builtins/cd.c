/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amimouni <amimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 05:51:14 by amimouni          #+#    #+#             */
/*   Updated: 2022/11/29 22:00:59 by amimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell2.h"
#include <errno.h>
#include <string.h>
#include <unistd.h>

static void	print_error(char **args)
{
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(args[1], 2);
}

static char	*check_env_path(t_list_env *env, t_list_env *export_env,
		char *env_path)
{
	update_oldpwd(env);
	update_oldpwd(export_env);
	env_path = get_env_path(env, "HOME", 4);
	return (env_path);
}

static int	func(t_list_env *env, t_list_env *export_env, int ret,
		char *env_paths)
{
	ret = chdir(env_paths);
	update_pwd(env);
	update_pwd(export_env);
	ft_memdel(env_paths);
	return (ret);
}

static int	go_to_path(t_list_env *env, t_list_env *export_env, int op)
{
	int		ret;
	char	*env_paths;

	env_paths = NULL;
	ret = 0;
	if (op == 0)
	{
		env_paths = check_env_path(env, export_env, env_paths);
		if (!env_paths)
		{
			ft_putendl_fd("minishell : cd: HOME not set", STDERR);
			return (1);
		}
	}
	if (op == 1)
	{
		env_paths = get_env_path(env, "OLDPWD", 6);
		if (!env_paths)
		{
			ft_putendl_fd("minishell : cd: OLDPWD not set", STDERR);
			return (1);
		}
		updated_pwd(env, export_env);
	}
	return (func(env, export_env, ret, env_paths));
}

int	ft_cd(char **args, t_list_env *env, t_list_env *export_env)
{
	int		cd_ret;
	char	*str;

	if (!args[1])
		return (go_to_path(env, export_env, 0));
	if (ft_strcmp(args[1], "-") == 0)
	{
		cd_ret = go_to_path(env, export_env, 1);
		str = get_env_path(env, "PWD", 3);
		ft_putendl_fd(str, 1);
		free(str);
	}
	else
	{
		update_oldpwd(env);
		update_oldpwd(export_env);
		cd_ret = chdir(args[1]);
		update_pwd(env);
		update_pwd(export_env);
		if (cd_ret < 0)
			cd_ret *= -1;
		if (cd_ret != 0)
			print_error(args);
	}
	return (cd_ret);
}

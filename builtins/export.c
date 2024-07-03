/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amimouni <amimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 06:15:28 by amimouni          #+#    #+#             */
/*   Updated: 2022/11/26 10:35:57 by amimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell2.h"
#include <stdio.h>

static int	print_error(int error, const char *arg)
{
	int	i;

	if (error == 0 || error == -3 || error == -1)
		ft_putstr_fd("export: not a valid identifier: ", STDERR);
	i = 0;
	while (arg[i] && (arg[i] != '=' || error == -3))
	{
		write(STDERR, &arg[i], 1);
		i++;
	}
	write(STDERR, "\n", 1);
	return (1);
}

char	*get_env_name(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i] && src[i] != '=' && ft_strlen(src) < BUFF_SIZE)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	is_in_env(t_list_env *env, char *args)
{
	char	var_name[BUFF_SIZE];
	char	env_name[BUFF_SIZE];

	get_env_name(var_name, args);
	while (env && env->next)
	{
		get_env_name(env_name, env->value);
		if (ft_strcmp(var_name, env_name) == 0)
		{
			ft_memdel(env->value);
			env->value = ft_strdup(args);
			return (1);
		}
		env = env->next;
	}
	return (0);
}

int	export_env(char **args, t_list_env *env,
		t_list_env *env_exp, int i)
{
	int	error_ret;
	int	new_env;

	new_env = 0;
	while (args[++i])
	{
		if (args[i][0] == '\0')
			print_error(0, args[i]);
		error_ret = is_valid_env(args[i]);
		if (args[i][0] == '=')
			error_ret = -3;
		if (error_ret <= 0)
			print_error(error_ret, args[i]);
		if (error_ret == 2)
			new_env = 1;
		else
			new_env = is_in_env(env, args[i]);
		if (new_env == 1 && !is_in_env(env_exp, args[i]))
			env_add(args[i], env_exp);
		if (new_env == 0)
			export_enva(args[i], env_exp, error_ret, env);
	}
	return (0);
}

int	run_export(char **args, t_list_env *env, t_list_env *expo_env)
{
	int	i;

	i = 0;
	if (!args[1])
	{
		print_sorted_env(expo_env);
		return (0);
	}
	else
		return (export_env(args, env, expo_env, i));
}

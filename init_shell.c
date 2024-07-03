/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amimouni <amimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 05:31:29 by amimouni          #+#    #+#             */
/*   Updated: 2022/11/29 11:10:44 by amimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell2.h"

static void	fill_env(t_list_env *new, char **env_array, t_list_env *env)
{
	int	i;

	i = 1;
	while (env_array && env_array[0] && env_array[i])
	{
		new = malloc(sizeof(t_list_env));
		if (!new)
			return ;
		new->value = ft_strdup(env_array[i]);
		new->next = NULL;
		env->next = new;
		env = new;
		i++;
	}
}

int	init_env(t_shell *mini, char **env_array)
{
	t_list_env	*env;
	t_list_env	*new;

	new = NULL;
	env = malloc(sizeof(t_list_env));
	if (!env)
		return (1);
	if (!env_array[0])
	{
		env->value = ft_strdup("");
		env->next = NULL;
		mini->env = env;
		return (0);
	}
	env->value = ft_strdup(env_array[0]);
	env->next = NULL;
	mini->env = env;
	fill_env(new, env_array, env);
	return (0);
}

int	init_export_env(t_shell *mini, char **env_array)
{
	t_list_env	*env;
	t_list_env	*new;

	new = NULL;
	env = malloc(sizeof(t_list_env));
	if (!env)
		return (1);
	if (!env_array[0])
	{
		env->value = ft_strdup("");
		env->next = NULL;
		mini->export_env = env;
		return (0);
	}	
	env->value = ft_strdup(env_array[0]);
	env->next = NULL;
	mini->export_env = env;
	fill_env(new, env_array, env);
	return (0);
}

void	init_shell(t_shell *t_mini)
{
	t_mini->in = dup(STDIN);
	t_mini->out = dup(STDOUT);
	t_mini->ret = 0;
	t_mini->no_exec = 0;
}

char	**put_in_tab(t_shell *mini)
{
	int			i;
	char		**env;
	t_list_env	*head;

	i = 0;
	head = mini->env;
	while (mini->env)
	{
		i++;
		mini->env = mini->env->next;
	}
	mini->env = head;
	env = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (mini->env)
	{
		env[i] = ft_strdup(mini->env->value);
		mini->env = mini->env->next;
		i++;
	}
	mini->env = head;
	env[i] = NULL;
	return (env);
}

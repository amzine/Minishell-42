/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amimouni <amimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 08:43:40 by amimouni          #+#    #+#             */
/*   Updated: 2022/11/25 23:28:15 by amimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell2.h"

void	check_env(char **a, t_shell *mini, t_list_env *env, t_list_env *tmp)
{
	int	i;

	i = 1;
	while (a[i])
	{
		while (env && env->next)
		{
			if (ft_strncmp(a[i], env->next->value, ft_strlen(a[i])) == 0)
			{
				tmp = env->next->next;
				free_node(mini, env->next);
				env->next = tmp;
				break ;
			}
			env = env->next;
		}
		env = mini->env;
		i++;
	}
}

void	check(char **a, t_shell *mini, t_list_env *export_env, t_list_env *tmp)
{
	int	i;

	i = 1;
	while (a[i])
	{
		while (export_env && export_env->next)
		{
			if (ft_strncmp(a[i], export_env->next->value, ft_strlen(a[i])) == 0)
			{
				tmp = export_env->next->next;
				free_node(mini, export_env->next);
				export_env->next = tmp;
				break ;
			}
			export_env = export_env->next;
		}
		export_env = mini->export_env;
		i++;
	}
}

int	run_unset(char **a, t_shell *mini)
{
	t_list_env	*env;
	t_list_env	*export_env;
	t_list_env	*tmp;
	int			i;

	tmp = NULL;
	i = 1;
	env = mini->env;
	export_env = mini->export_env;
	if (!(a[1]))
		return (0);
	check_env(a, mini, env, tmp);
	check(a, mini, export_env, tmp);
	return (0);
}

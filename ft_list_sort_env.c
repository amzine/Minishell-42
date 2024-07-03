/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_sort_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amimouni <amimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 06:25:01 by amimouni          #+#    #+#             */
/*   Updated: 2022/11/29 10:21:35 by amimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell2.h"

int	str_env_len(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

int	env_add(const char *value, t_list_env *env)
{
	t_list_env	*new;
	t_list_env	*tmp;

	if (env && env->value == NULL)
	{
		env->value = ft_strdup(value);
		return (0);
	}
	new = malloc(sizeof(t_list_env));
	if (!new)
		return (-1);
	new->value = ft_strdup(value);
	while (env && env->next && env->next->next)
		env = env->next;
	tmp = env->next;
	env->next = new;
	new->next = tmp;
	return (0);
}

void	sort_env(char **tabs, int env_len)
{
	int		ordered;
	int		i;
	char	*tmp;

	ordered = 0;
	while (tabs && ordered == 0)
	{
		ordered = 1;
		i = 0;
		while (i < env_len - 1)
		{
			if (ft_strcmp(tabs[i], tabs[i + 1]) > 0)
			{
				tmp = tabs[i];
				tabs[i] = tabs[i + 1];
				tabs[i + 1] = tmp;
				ordered = 0;
			}
			i++;
		}
		env_len--;
	}
}

void	print_sorted_env(t_list_env *env)
{
	int		i;
	char	**tabs;
	char	*str_env;

	str_env = env_to_str(env, 0, 0);
	tabs = ft_split(str_env, '\n');
	ft_memdel(str_env);
	sort_env(tabs, str_env_len(tabs));
	i = 0;
	while (tabs[i])
	{
		ft_putstr_fd("declare -x ", STDOUT);
		ft_putendl_fd(tabs[i], STDOUT);
		i++;
	}
	free_tab(tabs);
}

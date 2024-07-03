/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_oldpwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amimouni <amimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 06:51:02 by amimouni          #+#    #+#             */
/*   Updated: 2022/11/29 22:02:55 by amimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell2.h"

static char	*env_path(t_list_env *env, int len)
{
	int		s_alloc;
	int		i;
	int		j;
	char	*oldpwd;

	s_alloc = ft_strlen(env->value) - len;
	oldpwd = malloc(sizeof(char) * s_alloc + 1);
	if (!oldpwd)
		return (NULL);
	i = 0;
	j = 0;
	while (env->value[i])
	{
		if (i > len)
			oldpwd[j++] = env->value[i];
		i++;
	}
	oldpwd[j] = '\0';
	return (oldpwd);
}

char	*get_env_path(t_list_env *env, const char *var, int len)
{
	while (env && env->next != NULL)
	{
		if (ft_strncmp(env->value, var, len) == 0)
			return (env_path(env, len));
		env = env->next;
	}
	return (NULL);
}

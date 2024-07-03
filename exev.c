/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exev.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amimouni <amimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 03:08:13 by amimouni          #+#    #+#             */
/*   Updated: 2022/11/25 23:10:51 by amimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell2.h"

int	exev(char *path, char **av, t_list_env *env)
{
	int		ret;
	char	**env_arr;
	char	*ptr;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	ptr = env_to_str(env, 0, 0);
	env_arr = ft_split(ptr, '\n');
	free(ptr);
	if (ft_strchr(path, '/') != NULL)
		ret = execve(path, av, env_arr);
	ret = error_print(path);
	free_exit(env_arr, ret);
	return (ret);
}

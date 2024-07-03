/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amimouni <amimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 06:36:35 by amimouni          #+#    #+#             */
/*   Updated: 2022/11/29 10:35:34 by amimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell2.h"
#include <stdio.h>

int	run_env(t_list_env *env)
{
	while (env && env->next != NULL)
	{
		ft_putendl_fd(env->value, STDOUT);
		env = env->next;
	}
	if (env)
		ft_putendl_fd(env->value, STDOUT);
	return (0);
}

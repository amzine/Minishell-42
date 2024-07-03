/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amimouni <amimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 22:37:39 by amimouni          #+#    #+#             */
/*   Updated: 2022/11/25 22:54:00 by amimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell2.h"

void	export_enva(char *args, t_list_env *env_exp, int error_ret,
		t_list_env *env)
{
	if (error_ret == 1)
		env_add(args, env);
	if (!is_in_env(env_exp, args))
		env_add(args, env_exp);
}

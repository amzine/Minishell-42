/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_pwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amimouni <amimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 08:15:12 by amimouni          #+#    #+#             */
/*   Updated: 2022/11/27 08:19:46 by amimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell2.h"

void	updated_pwd(t_list_env *env, t_list_env *export_env)
{
	update_oldpwd(env);
	update_oldpwd(export_env);
}

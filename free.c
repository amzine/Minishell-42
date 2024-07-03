/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amimouni <amimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 06:29:07 by amimouni          #+#    #+#             */
/*   Updated: 2022/11/23 07:45:51 by amimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell2.h"

void	free_token(t_shell *t_mini)
{
	t_minishell	*head;
	int			i;

	i = 0;
	while (t_mini->start[i])
	{
		while (t_mini->start[i])
		{
			free(t_mini->start[i]->data);
			head = t_mini->start[i]->next;
			free(t_mini->start[i]);
			t_mini->start[i] = head;
		}
		i++;
	}
	free(t_mini->start);
}

void	free_node_export(t_shell *mini, t_list_env *env)
{
	if (mini->export_env == env && env->next == NULL)
	{
		ft_memdel(mini->export_env->value);
		mini->export_env->value = NULL;
		mini->export_env->next = NULL;
		return ;
	}
	ft_memdel(env->value);
	ft_memdel(env);
}

void	free_node(t_shell *mini, t_list_env *env)
{
	if (mini->env == env && env->next == NULL)
	{
		ft_memdel(mini->env->value);
		mini->env->value = NULL;
		mini->env->next = NULL;
		return ;
	}
	ft_memdel(env->value);
	ft_memdel(env);
}

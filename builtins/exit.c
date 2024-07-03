/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amimouni <amimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 06:19:46 by amimouni          #+#    #+#             */
/*   Updated: 2022/11/25 00:11:58 by amimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell2.h"
#include <stdio.h>

static int	isstrint(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
	}
	return (1);
}

void	run_exit(char **av, t_shell *mini)
{
	int	tmp;

	printf("exit\n");
	if (av[1] != 0)
	{
		if (isstrint(av[1]) == 0)
		{
			printf("minishell: exit : %s: numeric argument required", av[1]);
			exit(255);
		}
		else if (av[2] != 0)
			printf("minishell : exit : too many arguments");
		else
		{
			tmp = ft_atoi(av[1]);
			mini->ret = ft_atoi(av[1]);
			exit(tmp);
		}
	}
	else
		exit(0);
}

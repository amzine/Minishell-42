/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amimouni <amimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 08:09:46 by amimouni          #+#    #+#             */
/*   Updated: 2022/11/25 23:17:56 by amimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell2.h"

static
void	quit_process(int num)
{
	num++;
	printf("Quit: 3\n");
	g_sig.sigquit = 1;
	g_sig.exit_status = 131;
}

void	signal_for_blocking_cmd(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, quit_process);
}

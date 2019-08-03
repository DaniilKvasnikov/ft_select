/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 11:45:16 by rrhaenys          #+#    #+#             */
/*   Updated: 2019/08/03 11:53:50 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void
	stop_signal(void)
{
	reset_default_conf();
	free_args();
	exit(1);
}

void
	sig_handler(int signo)
{
	if (signo == SIGTSTP)
		reset_default_conf();
	else if (signo == SIGINT || signo == SIGABRT || signo == SIGSTOP
			|| signo == SIGKILL || signo == SIGQUIT)
		stop_signal();
	else if (signo == SIGCONT)
	{
		set_keypress();
		init_signals();
		print_list_select();
	}
	else if (signo == SIGWINCH)
		print_list_select();
}

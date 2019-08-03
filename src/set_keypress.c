/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_keypress.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 11:32:34 by rrhaenys          #+#    #+#             */
/*   Updated: 2019/08/03 11:53:10 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void
	set_keypress(void)
{
	if (tgetent(NULL, getenv("TERM")) == 0)
	{
		ft_putstr_fd("Error with TERM.\n", 2);
		exit(1);
	}
	tcgetattr(0, &g_mydata.old_settings);
	g_mydata.new_settings = g_mydata.old_settings;
	g_mydata.new_settings.c_lflag &= ~(ICANON | ECHO);
	g_mydata.new_settings.c_cc[VTIME] = 0;
	g_mydata.new_settings.c_cc[VMIN] = 1;
	tcsetattr(0, TCSANOW, &g_mydata.new_settings);
	return ;
}

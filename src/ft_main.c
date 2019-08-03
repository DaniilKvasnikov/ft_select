/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 11:48:05 by rrhaenys          #+#    #+#             */
/*   Updated: 2019/08/03 12:00:07 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static int
	one_char_input(char c)
{
	if (c == ESC_KEY)
		return (1);
	else if (c == SPC_KEY || c == ENTER_KEY)
	{
		set_select();
		muve_curr(1, ft_get_size_win_console(), get_max_size_select());
	}
	else if (c == BSP_KEY)
	{
		if (ft_delete_strs() == 1)
			return (1);
		muve_curr(0, ft_get_size_win_console(), get_max_size_select());
	}
	else if ((c >= 'A' && c <= 'Z') ||
				(c >= 'a' && c <= 'z') ||
				(c >= '0' && c <= '9'))
	{
		if (select_char(c) == 0)
			return (2);
	}
	else if (c == STAR_KEY)
		select_all();
	else
		return (2);
	return (0);
}

static int
	ft_select_body(void)
{
	char		c[4];
	int			ret;
	int			res;

	ret = read(STDERR_FILENO, &c, 4);
	if (ret == 1)
	{
		if ((res = one_char_input(c[0])) == 1)
			return (1);
		else if (res == 2)
			return (2);
	}
	else if (ret == 3 && c[0] == '\033')
	{
		if (c[2] == RIGHT_KEY || c[2] == DOWN_KEY)
			muve_curr(1, ft_get_size_win_console(), get_max_size_select());
		else if (c[2] == LEFT_KEY || c[2] == UP_KEY)
			muve_curr(-1, ft_get_size_win_console(), get_max_size_select());
		else
			return (2);
	}
	else
		return (2);
	return (0);
}

int
	main(int argc, char **argv)
{
	char		c[4];
	int			ret;
	int			res;

	if (argc <= 1)
		return (0);
	init_signals();
	init_mydata(argc, argv);
	set_keypress();
	print_list_select();
	while (get_strs_len(g_mydata.strs) != 0)
	{
		if ((res = ft_select_body()) == 1)
			break ;
		else if (res == 2)
			continue ;
		print_list_select();
	}
	reset_default_conf();
	print_list_result(STDOUT_FILENO);
	free_args();
	return (0);
}

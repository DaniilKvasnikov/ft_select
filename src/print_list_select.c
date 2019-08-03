/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_list_select.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 11:34:58 by rrhaenys          #+#    #+#             */
/*   Updated: 2019/08/03 11:52:14 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void
	main_print(int i, int max_size)
{
	int			j;

	if (g_mydata.type[i] == TYPE_BIN)
		ft_putstr_fd(TYPE_BIN_COLOR, 0);
	else if (g_mydata.type[i] == TYPE_DIR)
		ft_putstr_fd(TYPE_DIR_COLOR, 0);
	else if (g_mydata.type[i] == TYPE_LNK)
		ft_putstr_fd(TYPE_LNK_COLOR, 0);
	if (g_mydata.curr == i)
		ft_putstr_fd(STYLE_UNDERSCOPE, 0);
	if (g_mydata.active[i] == 1)
		ft_putstr_fd(STYLE_REVERSE, 0);
	ft_putstr_fd(g_mydata.strs[i], 0);
	ft_putstr_fd(C_RESET, 0);
	j = -1;
	while ((j + ft_strlen(g_mydata.strs[i])) < max_size)
	{
		ft_putchar_fd(' ', 0);
		j++;
	}
}

static int
	max_count_words(t_point2 size, int max_size)
{
	int		in_line;

	in_line = size.y / max_size;
	return (size.x * in_line);
}

static void
	print_list_select_vertical(t_point2 size, int max_size)
{
	int			i;
	int			j;
	int			count;

	count = get_strs_len(g_mydata.strs);
	i = -1;
	while (g_mydata.strs[++i] != NULL && i < size.x)
	{
		if (i != 0)
			ft_putchar_fd('\n', 0);
		j = g_mydata.curr_line;
		while ((i + j * size.x) < count &&
				j < (g_mydata.curr_line + size.y / max_size - 1))
		{
			main_print(i + j * size.x, max_size);
			j++;
		}
	}
}

void
	print_list_select(void)
{
	t_point2	size;
	int			max_size;

	muve_curr(0, ft_get_size_win_console(), get_max_size_select());
	ft_putstr_fd(CL, 0);
	size = ft_get_size_win_console();
	max_size = get_max_size_select();
	print_list_select_vertical(size, max_size);
}

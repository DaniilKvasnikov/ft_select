/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   muve_curr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 11:43:31 by rrhaenys          #+#    #+#             */
/*   Updated: 2019/08/03 11:47:16 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void
	muve_curr(int dx, t_point2 size_ter, int max_size)
{
	int	size;
	int	cur_line;

	size = get_strs_len(g_mydata.strs);
	g_mydata.curr += dx;
	if (g_mydata.curr < 0)
		g_mydata.curr += size;
	g_mydata.curr %= size;
	cur_line = g_mydata.curr / (int)size_ter.x;
	while (cur_line > (g_mydata.curr_line + size_ter.y / max_size - 1))
		g_mydata.curr_line++;
	if (cur_line < g_mydata.curr_line)
		g_mydata.curr_line = cur_line;
}

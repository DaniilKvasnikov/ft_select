/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 11:45:50 by rrhaenys          #+#    #+#             */
/*   Updated: 2019/08/03 11:46:31 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static int
	get_first_char(char *str)
{
	int	i;

	i = -1;
	while (str[++i] != '\0')
		;
	while (--i >= 0)
		if (str[i] == '/')
			return (i + 1);
	return (0);
}

int
	select_char(char c)
{
	int	i;
	int	j;

	i = g_mydata.curr;
	while (g_mydata.strs[++i] != NULL)
	{
		j = get_first_char(g_mydata.strs[i]);
		if (g_mydata.strs[i][j] == c)
		{
			g_mydata.curr = i;
			return (1);
		}
	}
	i = -1;
	while (++i < g_mydata.curr)
	{
		j = get_first_char(g_mydata.strs[i]);
		if (g_mydata.strs[i][j] == c)
		{
			g_mydata.curr = i;
			return (1);
		}
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_list_result.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 11:41:49 by rrhaenys          #+#    #+#             */
/*   Updated: 2019/08/03 11:47:34 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void
	print_list_result(int fd)
{
	int	i;
	int	j;

	ft_putstr_fd(CL, 0);
	i = -1;
	j = 0;
	while (g_mydata.strs[++i] != NULL)
	{
		if (g_mydata.active[i] == 1)
		{
			if (j != 0)
				ft_putchar_fd(' ', fd);
			ft_putstr_fd(g_mydata.strs[i], fd);
			j++;
		}
	}
	if (j != 0)
		ft_putchar_fd('\n', fd);
}

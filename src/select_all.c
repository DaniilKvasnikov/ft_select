/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_all.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 11:40:16 by rrhaenys          #+#    #+#             */
/*   Updated: 2019/08/03 11:47:19 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void
	select_all(void)
{
	int		b;
	int		i;

	i = -1;
	b = 0;
	while (g_mydata.strs[++i] != NULL)
		if (g_mydata.active[i] == 0)
			b = 1;
	i = -1;
	while (g_mydata.strs[++i] != NULL)
		g_mydata.active[i] = b;
}

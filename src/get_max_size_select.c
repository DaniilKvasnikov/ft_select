/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_max_size_select.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 11:41:23 by rrhaenys          #+#    #+#             */
/*   Updated: 2019/08/03 11:44:45 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int
	get_max_size_select(void)
{
	int	max;
	int	i;

	max = ft_strlen(g_mydata.strs[0]);
	i = -1;
	while (g_mydata.strs[++i] != NULL)
		if (ft_strlen(g_mydata.strs[i]) > max)
			max = ft_strlen(g_mydata.strs[i]);
	return (max);
}

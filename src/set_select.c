/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_select.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 11:46:39 by rrhaenys          #+#    #+#             */
/*   Updated: 2019/08/03 11:46:51 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void
	set_select(void)
{
	g_mydata.active[g_mydata.curr] = !g_mydata.active[g_mydata.curr];
}

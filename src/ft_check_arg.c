/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 01:00:29 by vrybalko          #+#    #+#             */
/*   Updated: 2017/03/05 14:50:27 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void		enable_flag(t_e *e, char *arg)
{
	int		i;

	i = -1;
	while (arg[++i] != '\0')
	{
		if (arg[i] == 'l')
			e->fl.list = 1;
		else if (arg[i] == 'R')
			e->fl.rec = 1;
		else if (arg[i] == 'r')
			e->fl.rev = 1;
		else if (arg[i] == 'a')
			e->fl.all = 1;
		else if (arg[i] == 't')
			e->fl.time = 1;
	}
}

void		check_arg(t_e *e, char *arg)
{
	if (arg[0] == '-' && arg[1] != '\0')
		enable_flag(e, arg);
	else
		read_arg(e, arg);
}

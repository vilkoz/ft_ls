/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 00:52:02 by vrybalko          #+#    #+#             */
/*   Updated: 2017/03/06 17:57:03 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void		init_e(t_e *e)
{
	e->fl.list = 0;
	e->fl.rec = 0;
	e->fl.rev = 0;
	e->fl.all = 0;
	e->fl.time = 0;
	e->va = 0;
	e->lst = NULL;
}

int			main(int argc, char **argv)
{
	t_e		e;
	int		i;

	init_e(&e);
	if (argc == 1)
	{
		read_arg(&e, ".");
		return (0);
	}
	i = 0;
	while (++i < argc)
		check_arg(&e, argv[i]);
	i = 0;
	e.va = 0;
	while (++i < argc)
		if (argv[i][0] != '-' && (e.va = 1))
			read_arg(&e, argv[i]);
		else if (e.va == 1)
			read_arg(&e, argv[i]);
	if (e.va == 0)
		read_arg(&e, ".");
	return (0);
}

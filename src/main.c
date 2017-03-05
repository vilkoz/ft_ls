/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 00:52:02 by vrybalko          #+#    #+#             */
/*   Updated: 2017/03/05 16:16:31 by vrybalko         ###   ########.fr       */
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
}

int			main(int argc, char **argv)
{
	t_e		e;
	int		i;

	if (argc == 1)
		return (0);
	i = 0;
	while (++i < argc)
		check_arg(&e, argv[i]);
	return (0);
}

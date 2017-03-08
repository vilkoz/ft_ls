/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 00:52:02 by vrybalko          #+#    #+#             */
/*   Updated: 2017/03/08 20:40:14 by vrybalko         ###   ########.fr       */
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
	e->ret = 0;
}

int			invalid_arg(char *arg)
{
	int		i;
	char	*msg;

	i = 0;
	while (arg[++i] != 0)
		if (is_flag(arg[i]) == 0)
		{
			msg = (char *)malloc(sizeof(char) * 28);
			msg = ft_strcpy(msg, "./ft_ls: illegal option --  ");
			msg[27] = arg[i];
			ft_putendl(msg);
			ft_putendl("usage: ./ft_ls [-alrtR] [file ...]");
			free(msg);
			return (1);
		}
	return (1);
}

int			main(int argc, char **argv)
{
	t_e		e;
	int		i;

	init_e(&e);
	if (argc == 1)
	{
		read_arg(&e, ft_strdup("."));
		return (0);
	}
	i = 0;
	while (++i < argc)
		check_arg(&e, argv[i]);
	i = 0;
	e.va = 0;
	while (++i < argc)
		if (!is_arg_flag(argv[i]) && argv[i][0] != '-' && (e.va = 1))
			read_arg(&e, ft_strdup(argv[i]));
		else if (e.va == 1)
			read_arg(&e, ft_strdup(argv[i]));
		else if (argv[i][0] == '-' && !is_arg_flag(argv[i]))
			return (invalid_arg(argv[i]));
	if (e.va == 0)
		read_arg(&e, ft_strdup("."));
	return (e.ret);
}

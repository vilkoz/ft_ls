/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 00:52:02 by vrybalko          #+#    #+#             */
/*   Updated: 2017/03/10 15:58:04 by vrybalko         ###   ########.fr       */
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
	e->print_dir_name = 0;
	e->arg_conunt = 0;
	e->arg_num = 0;
	e->was_solo = 0;
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

void		print_solo(t_e *e)
{
	if (e->lst == NULL)
		return ;
	ft_sort(e, e->lst);
	print_list(e, e->lst);
	ft_lstdel(&e->lst, lst_clear);
}

void		check_solo(t_e *e, char *arg)
{
	t_arg	*a;

	if ((is_folder(arg) == 1) ||
		(is_folder(arg) == 2 && e->fl.list == 0))
		return ;
	else if (is_arg_flag(arg) == 0 || is_folder(arg) == 3)
	{
		if ((a = stat_format(e, &arg)) == NULL)
			return ;
		a->is_solo = 1;
		e->print_dir_name = 1;
		ft_lstadd(&e->lst, ft_lstnew((void *)a, sizeof(t_arg)));
	}
	ft_memdel((void *)&arg);
}

int			main(int argc, char **argv)
{
	t_e		e;
	int		i;

	init_e(&e);
	i = 0;
	while (++i < argc)
	{
		check_arg(&e, argv[i]);
		check_solo(&e, ft_strdup(argv[i]));
	}
	print_solo(&e);
	i = 0;
	e.va = 0;
	while (++i < argc)
		if ((!is_arg_flag(argv[i]) && is_folder(argv[i]) && argv[i][0] == '-'
		&& (e.va = 1)) || (!is_arg_flag(argv[i]) && argv[i][0] != '-'
		&& (e.va = 1)))
			read_arg(&e, ft_strdup(argv[i]));
		else if (argv[i][0] == '-' && !is_arg_flag(argv[i]))
			return (invalid_arg(argv[i]));
		else if (e.va == 1)
			read_arg(&e, ft_strdup(argv[i]));
	if (e.va == 0)
		read_arg(&e, ft_strdup("."));
	return (e.ret);
}

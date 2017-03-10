/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_arg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 14:47:40 by vrybalko          #+#    #+#             */
/*   Updated: 2017/03/10 17:07:34 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

t_arg	*init_arg(t_e *e, t_stat *s, char *name)
{
	t_arg	*arg;
	char	*buf;

	arg = (t_arg *)malloc(sizeof(t_arg));
	arg->stat = (t_stat *)malloc(sizeof(t_stat));
	arg->stat = ft_memcpy((void*)arg->stat, (void*)s, sizeof(t_stat));
	arg->name = ft_strdup(name);
	if (e->fl.list == 1 && S_ISLNK(s->st_mode))
	{
		buf = ft_strnew(255);
		readlink(name, buf, 255);
		arg->targ_link = ft_fj(ft_strdup(" -> "), ft_strdup(buf));
		free(buf);
	}
	else
		arg->targ_link = NULL;
	arg->rights = (e->fl.list == 1) ? ft_strnew(11) : NULL;
	arg->nlinks = NULL;
	arg->user = NULL;
	arg->group = NULL;
	arg->size = NULL;
	arg->time = NULL;
	arg->is_solo = 0;
	return (arg);
}

t_arg	*stat_format(t_e *e, char **arg)
{
	t_stat		s;
	t_arg		*a;

	if ((lstat(*arg, &s)) == -1)
	{
		e->ret = 1;
		return (NULL);
	}
	a = init_arg(e, &s, *arg);
	if (e->fl.list == 1)
	{
		print_type(s, a);
		print_rights(s, a);
		print_nlink(s, a);
		print_user(s, a);
		print_size(s, a);
		print_time(s, a);
	}
	free(*arg);
	*arg = NULL;
	return (a);
}

void	lst_clear(void *a1, size_t size)
{
	t_arg	*a;

	(void)size;
	a = (t_arg *)a1;
	ft_strdel(&a->rights);
	ft_strdel(&a->nlinks);
	ft_strdel(&a->user);
	ft_strdel(&a->group);
	ft_strdel(&a->size);
	ft_strdel(&a->time);
	ft_strdel(&a->name);
	free(a->stat);
	free(a);
}

void	recursive(t_list *l1, t_len *len)
{
	t_arg	*arg;

	arg = ((t_arg*)l1->content);
	if ((len->fl.all == 0 && len->fl.rec == 1 && is_folder(arg->name) == 1)
		|| (len->fl.all == 1 && len->fl.rec
		&& (ft_strcmp(ft_strrchr(arg->name, '/') + 1, "..") != 0
		&& ft_strcmp(ft_strrchr(arg->name, '/') + 1, ".") != 0
		&& is_folder(arg->name) == 1)))
	{
		ft_putchar('\n');
		ft_putstr(arg->name);
		ft_putendl(":");
		read_arg(len->e, ft_strdup(arg->name));
	}
}

void	read_arg(t_e *e, char *arg)
{
	t_list	*lst;
	t_len	len;
	t_arg	*a;

	lst = NULL;
	if (e->arg_conunt >= 2)
		e->print_dir_name = 1;
	if ((is_folder(arg) == 1) || (is_folder(arg) == 2 && e->fl.list == 0))
		open_dir(e, arg, &lst);
	else
	{
		if ((a = stat_format(e, &arg)) == NULL)
		{
			perror(ft_strjoin("./ft_ls: ", arg));
			return ;
		}
		return ;
	}
	ft_sort(e, lst);
	print_list(e, lst);
	init_len(&len, e);
	lst_iter_len(lst, recursive, &len);
	ft_lstdel(&lst, lst_clear);
	ft_memdel((void**)&arg);
}

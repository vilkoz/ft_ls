/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 16:12:45 by vrybalko          #+#    #+#             */
/*   Updated: 2017/03/07 16:11:26 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void		format_print(char *s, size_t max_len, int side)
{
	size_t		len;

	if (s == NULL)
		return ;
	len = ft_strlen(s);
	if (side == LEFT)
		ft_putstr(s);
	while (len < max_len)
	{
		ft_putchar(' ');
		len++;
	}
	if (side == RIGHT)
		ft_putstr(s);
}

void		print_list1(t_list *elem, t_len *len)
{
	t_arg	a;

	a = *(t_arg *)elem->content;
	format_print(a.rights, len->rights, RIGHT);
	ft_putstr("  ");
	format_print(a.nlinks, len->nlinks, RIGHT);
	ft_putstr(" ");
	format_print(a.user, len->user, LEFT);
	ft_putstr("  ");
	format_print(a.group, len->group, LEFT);
	ft_putstr("  ");
	format_print(a.size, len->size, RIGHT);
	ft_putchar(' ');
	format_print(a.time, len->time, RIGHT);
	ft_putchar(' ');
	ft_putendl(a.name);
}

void		print_list2(t_list *elem, t_len *len)
{
	t_arg	a;

	(void)len;
	a = *(t_arg *)elem->content;
	ft_putendl(a.name);
}

void		lst_iter_len(t_list *lst, void (*f)(t_list *l1, t_len *len),
						t_len *len)
{
	t_list		*tmp;

	tmp = lst;
	while (tmp)
	{
		f(tmp, len);
		tmp = tmp->next;
	}
}

void		count_len(t_list *l, t_len *len)
{
	t_arg	*a;
	size_t	size;

	a = (t_arg*)l->content;
	if (len->fl.list == 1 && len->fl.all == 0 && a->name[0] != '.')
		len->blocks += a->stat->st_blocks;
	else if (len->fl.list == 1 && len->fl.all == 1)
		len->blocks += a->stat->st_blocks;
	if (a->rights != NULL && ((size = ft_strlen(a->rights)) > len->rights))
		len->rights = size;
	if (a->nlinks != NULL && ((size = ft_strlen(a->nlinks)) > len->nlinks))
		len->nlinks = size;
	if (a->user != NULL && ((size = ft_strlen(a->user)) > len->user))
		len->user = size;
	if (a->group != NULL && ((size = ft_strlen(a->group)) > len->group))
		len->group = size;
	if (a->size != NULL && ((size = ft_strlen(a->size)) > len->size))
		len->size = size;
	if (a->time != NULL && ((size = ft_strlen(a->time)) > len->time))
		len->time = size;
}

void		init_len(t_len *len, t_e *e)
{
	len->rights = 0;
	len->nlinks = 0;
	len->user = 0;
	len->group = 0;
	len->size = 0;
	len->time = 0;
	len->blocks = 0;
	len->fl = e->fl;
}

void		print_list(t_e *e)
{
	t_list		*lst;
	t_len		len;

	lst = e->lst;
	init_len(&len, e);
	if (e->fl.list == 1)
	{
		lst_iter_len(lst, count_len, &len);
		ft_putstr("total ");
		ft_putnbr(len.blocks);
		ft_putchar('\n');
		lst_iter_len(lst, print_list1, &len);
	}
	else
		lst_iter_len(lst, print_list2, &len);
}

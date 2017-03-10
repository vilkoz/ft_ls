/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 16:12:45 by vrybalko          #+#    #+#             */
/*   Updated: 2017/03/10 17:11:15 by vrybalko         ###   ########.fr       */
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
	char	*tmp;

	a = *(t_arg *)elem->content;
	format_print(a.rights, len->rights, RIGHT);
	ft_putstr("  ");
	format_print(a.nlinks, len->nlinks, RIGHT);
	ft_putstr(" ");
	format_print(a.user, len->user, LEFT);
	ft_putstr("  ");
	format_print(a.group, len->group, LEFT);
	(!S_ISCHR(a.stat->st_mode)) ? ft_putstr("  ") : 23;
	format_print(a.size, len->size, RIGHT);
	ft_putchar(' ');
	format_print(a.time, len->time, RIGHT);
	ft_putchar(' ');
	if ((tmp = ft_strrchr(a.name, '/')) != NULL && a.is_solo == 0)
		ft_putstr(tmp + 1);
	else
		ft_putstr(a.name);
	ft_putendl(a.targ_link);
	(a.targ_link == NULL) ? ft_putchar('\n') : 23;
}

void		print_list2(t_list *elem, t_len *len)
{
	t_arg	a;
	char	*tmp;

	(void)len;
	a = *(t_arg *)elem->content;
	if ((tmp = ft_strrchr(a.name, '/')) != NULL && a.is_solo == 0)
		ft_putendl(tmp + 1);
	else
		ft_putendl(a.name);
}

int			is_hidden(char *name)
{
	char	*tmp;

	if (name == NULL)
		return (1);
	if (((tmp = ft_strrchr(name, '/')) != NULL) && tmp[0] != '.')
		return (0);
	else if (name[0] != '.')
		return (0);
	return (1);
}

void		print_list(t_e *e, t_list *head)
{
	t_list		*lst;
	t_len		len;

	lst = head;
	init_len(&len, e);
	if (e->fl.list == 1)
	{
		lst_iter_len(lst, count_len, &len);
		if (len.fl.list == 1 && e->lst == NULL && lst != NULL)
		{
			ft_putstr("total ");
			ft_putnbr(len.blocks);
			ft_putchar('\n');
		}
		lst_iter_len(lst, print_list1, &len);
	}
	else
		lst_iter_len(lst, print_list2, &len);
}

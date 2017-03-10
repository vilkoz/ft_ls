/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 17:08:26 by vrybalko          #+#    #+#             */
/*   Updated: 2017/03/10 17:12:22 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

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
	if (len->fl.list == 1 && len->fl.all == 0 &&
			!is_hidden(a->name))
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
	len->e = e;
}

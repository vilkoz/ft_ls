/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 01:29:48 by vrybalko          #+#    #+#             */
/*   Updated: 2017/03/07 20:33:54 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

int		lst_size(t_list *head)
{
	int		i;

	i = 0;
	while (head)
	{
		i++;
		head = head->next;
	}
	return (i);
}

void	lst_swap(t_list *l1, t_list *l2)
{
	void	*tmp;
	size_t	s_tmp;

	tmp = l1->content;
	s_tmp = l1->content_size;
	l1->content = l2->content;
	l1->content_size = l2->content_size;
	l2->content = tmp;
	l2->content_size = s_tmp;
}

void	ft_lstsort(t_list *head, int (*cmp)(t_list *l1, t_list *l2), int mode)
{
	int		size;
	int		i;
	t_list	*tmp;

	i = -1;
	size = lst_size(head);
	tmp = head;
	while (i < size && tmp->next)
	{
		if ((mode == 0) ? cmp(tmp, tmp->next) > 0 : cmp(tmp, tmp->next) < 0)
		{
			lst_swap(tmp, tmp->next);
			i = 0;
			tmp = head;
		}
		else
		{
			i++;
			tmp = tmp->next;
		}
	}
}

int		sort_alfa(t_list *l1, t_list *l2)
{
	return (ft_strcmp((*(t_arg*)l1->content).name,
		(*(t_arg*)l2->content).name));
}

int		sort_mtime(t_list *l1, t_list *l2)
{
	t_stat	*s1;
	t_stat	*s2;

	s1 = ((t_arg *)l1->content)->stat;
	s2 = ((t_arg *)l2->content)->stat;
	if (s2->st_mtimespec.tv_sec - s1->st_mtimespec.tv_sec != 0)
		return (s2->st_mtimespec.tv_sec - s1->st_mtimespec.tv_sec);
	else
		return (s2->st_mtimespec.tv_nsec - s1->st_mtimespec.tv_nsec);
}

void	ft_sort(t_e *e, t_list *head)
{
	t_list	*lst;

	if ((lst = head) == NULL)
		return ;
	if (e->fl.time == 1)
		ft_lstsort(lst, sort_mtime, e->fl.rev);
	else
		ft_lstsort(lst, sort_alfa, e->fl.rev);
}

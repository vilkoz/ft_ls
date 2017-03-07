/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 23:03:06 by vrybalko          #+#    #+#             */
/*   Updated: 2017/03/07 17:46:15 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void		read_rec_dir(t_e *e, char *arg)
{
	DIR			*dirp;
	t_dirent	*dir;

	if ((dirp = opendir(arg)) == NULL)
	{
		perror(arg);
		return ;
	}
	while ((dir = readdir(dirp)) != NULL)
	{
		if (e->fl.all != 1)
			if (dir->d_name[0] == '.')
				continue ;
		if (e->fl.rec == 1 && is_folder(dir->d_name) &&
				ft_strcmp(dir->d_name, ".") != 0 &&
				ft_strcmp(dir->d_name, "..") != 0)
			read_arg(e, ft_fj(ft_strdup(arg), ft_strjoin("/", dir->d_name)));
	}
	closedir(dirp);
}

void		open_dir(t_e *e, char *arg, t_list **lst)
{
	DIR			*dirp;
	t_dirent	*dir;
	t_arg		*a;

	if ((dirp = opendir(arg)) == NULL)
	{
		perror(arg);
		return ;
	}
	(e->fl.rec == 1) ? ft_putchar('\n') : 23;
	(e->fl.rec == 1) ? ft_putendl(arg) : 23;
	while ((dir = readdir(dirp)) != NULL)
	{
		if (e->fl.all != 1)
			if (dir->d_name[0] == '.')
				continue ;
		if ((a = stat_format(e, ft_fj(ft_strdup(arg),
			ft_strjoin("/", dir->d_name)))) == NULL)
			return ;
		ft_lstadd(lst, ft_lstnew((void *)a, sizeof(t_arg)));
		free(a);
	}
	closedir(dirp);
}

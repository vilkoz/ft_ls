/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 23:03:06 by vrybalko          #+#    #+#             */
/*   Updated: 2017/03/05 23:24:24 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void		open_dir(t_e *e, char *arg)
{
	DIR			*dirp;
	t_dirent	*dir;

	(void)e;
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
		if (e->fl.list)
			stat_format(e, ft_strjoin(arg, ft_strjoin("/", dir->d_name)));
		else
			ft_putendl(dir->d_name);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 16:38:09 by vrybalko          #+#    #+#             */
/*   Updated: 2017/03/10 16:38:47 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void	print_type(t_stat el, t_arg *a)
{
	if (S_ISREG(el.st_mode))
		a->rights[0] = '-';
	else if (S_ISDIR(el.st_mode))
		a->rights[0] = 'd';
	else if (S_ISFIFO(el.st_mode))
		a->rights[0] = 'p';
	else if (S_ISCHR(el.st_mode))
		a->rights[0] = 'c';
	else if (S_ISBLK(el.st_mode))
		a->rights[0] = 'b';
	else if (S_ISLNK(el.st_mode))
		a->rights[0] = 'l';
	else if (S_ISSOCK(el.st_mode))
		a->rights[0] = 's';
}

void	print_rights_u(t_stat el, t_arg *a)
{
	a->rights[1] = ((el.st_mode & S_IRUSR) != 0) ? 'r' : '-';
	a->rights[2] = ((el.st_mode & S_IWUSR) != 0) ? 'w' : '-';
	if ((el.st_mode & S_ISUID) && (el.st_mode & S_IXUSR))
		a->rights[3] = 's';
	else if ((el.st_mode & S_ISUID) && (el.st_mode & S_IXUSR) == 0)
		a->rights[3] = 'S';
	else if ((el.st_mode & S_ISUID) == 0 && (el.st_mode & S_IXUSR))
		a->rights[3] = 'x';
	else
		a->rights[3] = '-';
}

void	print_rights(t_stat el, t_arg *a)
{
	print_rights_u(el, a);
	a->rights[4] = ((el.st_mode & S_IRGRP) != 0) ? 'r' : '-';
	a->rights[5] = ((el.st_mode & S_IWGRP) != 0) ? 'w' : '-';
	a->rights[6] = ((el.st_mode & S_IXGRP) != 0) ? 'x' : '-';
	if ((el.st_mode & S_ISGID) && (el.st_mode & S_IXGRP))
		a->rights[6] = 's';
	else if ((el.st_mode & S_ISGID) && (el.st_mode & S_IXGRP) == 0)
		a->rights[6] = 'S';
	else if ((el.st_mode & S_ISGID) == 0 && (el.st_mode & S_IXGRP))
		a->rights[6] = 'x';
	else
		a->rights[6] = '-';
	a->rights[7] = ((el.st_mode & S_IROTH) != 0) ? 'r' : '-';
	a->rights[8] = ((el.st_mode & S_IWOTH) != 0) ? 'w' : '-';
	if ((el.st_mode & S_IXOTH) && (el.st_mode & S_ISVTX) == 0)
		a->rights[9] = 'x';
	else if ((el.st_mode & S_IXOTH) && (el.st_mode & S_ISVTX))
		a->rights[9] = 't';
	else if ((el.st_mode & S_IXOTH) == 0 && (el.st_mode & S_ISVTX))
		a->rights[9] = 'T';
	else
		a->rights[9] = '-';
}

void	print_nlink(t_stat el, t_arg *a)
{
	a->nlinks = ft_itoa(el.st_nlink);
}

void	print_user(t_stat el, t_arg *a)
{
	t_passwd	*p;
	t_group		*g;

	p = getpwuid(el.st_uid);
	a->user = ft_strdup(p->pw_name);
	g = getgrgid(el.st_gid);
	a->group = ft_strdup(g->gr_name);
}

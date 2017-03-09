/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_arg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 14:47:40 by vrybalko          #+#    #+#             */
/*   Updated: 2017/03/09 21:20:13 by vrybalko         ###   ########.fr       */
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

/*
**#define S_ISUID 0004000   set user id on execution
**#define S_ISGID 0002000   set group id on execution
**#define S_ISVTX 0001000   save swapped text even after use
*/

/*
** TODO: xattr show
*/

void	print_rights(t_stat el, t_arg *a)
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
	a->rights[4] = ((el.st_mode & S_IRGRP) != 0) ? 'r' : '-';
	a->rights[5] = ((el.st_mode & S_IWGRP) != 0) ? 'w' : '-';
	a->rights[6] = ((el.st_mode & S_IXGRP) != 0) ? 'x' : '-';
	// if ((el.st_mode & S_ISGID) && (el.st_mode & S_IXGRP))
	// 	a->rights[6] = 's';
	// else if ((el.st_mode & S_ISGID) && (el.st_mode & S_IXGRP) == 0)
	// 	a->rights[6] = 'S';
	// else if ((el.st_mode & S_ISGID) == 0 && (el.st_mode & S_IXGRP))
	// 	a->rights[6] = 'x';
	// else
	// 	a->rights[6] = '-';
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

char	*format_line(char *major, char *minor)
{
	size_t		l_maj;
	size_t		l_min;
	char		*res;

	l_maj = ft_strlen(major);
	l_min = ft_strlen(minor);
	res = ft_strnew(10);
	ft_memset((void *)res, ' ', 9);
	while (l_maj > 0)
	{
		res[l_maj - 1 + 4] = major[l_maj - 1];
		l_maj--;
	}
	while (l_min > 0)
	{
		res[l_min - 1 + 9] = minor[l_min - 1];
		l_min--;
	}
	res[5] = ',';
	free(minor);
	free(major);
	return (res);
}

void	print_size(t_stat el, t_arg *a)
{
	char	*major;
	char	*minor;

	if (S_ISCHR(el.st_mode) != 0)
	{
		major = ft_itoa(el.st_rdev & 0xff00u >> 8);
		minor = ft_itoa(minor(el.st_rdev));
		a->size = format_line(major, minor);
	}
	else
		a->size = ft_itoa(el.st_size);
}

void	print_time(t_stat el, t_arg *a)
{
	char			*t;
	long double		delta;

	t = ctime(&el.st_mtimespec.tv_sec);
	delta = time(NULL) - el.st_mtimespec.tv_sec;
	if ((delta > 0 && delta < SIXMONTH)
		|| (delta < 0 && delta > -SIXMONTH))
		t = ft_strsub(t, 4, 12);
	else
		t = ft_fj(ft_strsub(t, 4, 7),
			ft_strsub(t, 19, 5));
	a->time = t;
}

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

int		is_folder(char *arg)
{
	t_stat		tmp;

	if ((lstat(arg, &tmp)) == -1)
		return (-1);
	if (S_ISDIR(tmp.st_mode) && !S_ISLNK(tmp.st_mode))
		return (1);
	else if (S_ISLNK(tmp.st_mode) && S_ISDIR(tmp.st_mode))
		return (2);
	else if (S_ISLNK(tmp.st_mode) && !S_ISDIR(tmp.st_mode))
		return (3);
	else
		return (0);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_arg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 14:47:40 by vrybalko          #+#    #+#             */
/*   Updated: 2017/03/05 19:29:54 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

/*
** TODO: add stat to list
*/

void	print_type(t_stat el)
{
	if ((el.st_mode & S_IFREG) != 0)
		ft_putchar('-');
	else if ((el.st_mode & S_IFDIR) != 0)
		ft_putchar('d');
	else if ((el.st_mode & S_IFIFO) != 0)
		ft_putchar('p');
	else if ((el.st_mode & S_IFCHR) != 0)
		ft_putchar('c');
	else if ((el.st_mode & S_IFBLK) != 0)
		ft_putchar('b');
	else if ((el.st_mode & S_IFLNK) != 0)
		ft_putchar('l');
	else if ((el.st_mode & S_IFSOCK) != 0)
		ft_putchar('s');
}
/*
**#define S_ISUID 0004000   set user id on execution
**#define S_ISGID 0002000   set group id on execution
**#define S_ISVTX 0001000   save swapped text even after use
*/

/*
** TODO: xattr show
*/
void	print_rights(t_stat el)
{
	((el.st_mode & S_IRUSR)) ? ft_putchar('r') : ft_putchar('-');
	((el.st_mode & S_IWUSR)) ? ft_putchar('w') : ft_putchar('-');
	if ((el.st_mode & S_ISUID) && (el.st_mode & S_IXUSR))
		ft_putchar('s');
	else if ((el.st_mode & S_ISUID) && (el.st_mode & S_IXUSR) == 0)
		ft_putchar('S');
	else if ((el.st_mode & S_ISUID) == 0 && (el.st_mode & S_IXUSR))
		ft_putchar('x');
	else
		ft_putchar('-');
	((el.st_mode & S_IRGRP)) ? ft_putchar('r') : ft_putchar('-');
	((el.st_mode & S_IWGRP)) ? ft_putchar('w') : ft_putchar('-');
	((el.st_mode & S_IXGRP)) ? ft_putchar('x') : ft_putchar('-');
	((el.st_mode & S_IROTH)) ? ft_putchar('r') : ft_putchar('-');
	((el.st_mode & S_IWOTH)) ? ft_putchar('w') : ft_putchar('-');
	if ((el.st_mode & S_IXOTH) && (el.st_mode & S_ISVTX) == 0)
		ft_putchar('x');
	else if ((el.st_mode & S_IXOTH) && (el.st_mode & S_ISVTX))
		ft_putchar('t');
	else if ((el.st_mode & S_IXOTH) == 0 && (el.st_mode & S_ISVTX))
		ft_putchar('T');
	else
		ft_putchar('-');
}
/*
** TODO: count max size n_link in output
*/
void	print_nlink(t_stat el)
{
	ft_putstr("  ");
	ft_putnbr(el.st_nlink);
}

void	print_user(t_stat el)
{
	t_passwd	*p;
	t_group		*g;

	p = getpwuid(el.st_uid);
	ft_putstr(" ");
	ft_putstr(p->pw_name);
	g = getgrgid(el.st_gid);
	ft_putstr("  ");
	ft_putstr(g->gr_name);
}

void	print_size(t_stat el)
{
	ft_putstr("  ");
	ft_putnbr(el.st_size);
}

void	print_time(t_stat el)
{
	char	*time;
	char	*tmp;

	time = ctime(&el.st_mtimespec.tv_sec);
	tmp = time;
	time = ft_strsub(time, 4, 12);
	ft_putstr(" ");
	ft_putstr(time);
}

void	print_name(char *arg)
{
	char	*tmp;

	ft_putstr("  ");
	if ((tmp = ft_strrchr(arg, '/')) != NULL)
		ft_putstr(tmp + 1);
	else
		ft_putstr(arg);
}

void	stat_format(t_e *e, char *arg)
{
	t_stat		el;

	if ((stat(arg, &el)) == -1)
	{
		perror(arg);
		return ;
	}
	if (e->fl.list == 1)
	{
		print_type(el);
		print_rights(el);
		print_nlink(el);
		print_user(el);
		print_size(el);
		print_time(el);
		print_name(arg);
		ft_putchar('\n');
	}
}

int		is_folder(char *arg)
{
	t_stat		tmp;

	if ((stat(arg, &tmp)) == -1)
	{
		perror(arg);
		return (-1);
	}
	if (((tmp.st_mode) & S_IFDIR) != 0)
		return (1);
	else
		return (0);
}

void	read_arg(t_e *e, char *arg)
{
	is_folder(arg);
	stat_format(e, arg);
}

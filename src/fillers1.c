/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillers1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 16:39:10 by vrybalko          #+#    #+#             */
/*   Updated: 2017/03/10 17:05:06 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

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
	long double		ftime;
	long double		now;

	t = ctime(&el.st_mtimespec.tv_sec);
	now = time(NULL);
	ftime = el.st_mtimespec.tv_sec;
	if (ftime + SIXMONTH > now && ftime < now + SIXMONTH &&
		(ABS(now - ftime) > 30))
		t = ft_strsub(t, 4, 12);
	else
		t = ft_fj(ft_strsub(t, 4, 7),
			ft_strsub(t, 19, 5));
	a->time = t;
}

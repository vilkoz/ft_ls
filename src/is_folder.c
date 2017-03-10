/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_folder.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 17:01:44 by vrybalko          #+#    #+#             */
/*   Updated: 2017/03/10 17:01:55 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

int		is_folder(char *arg)
{
	t_stat		tmp;
	char		buf[256];
	size_t		end;

	if ((lstat(arg, &tmp)) == -1)
		return (-1);
	if (S_ISLNK(tmp.st_mode))
	{
		end = readlink(arg, buf, 256);
		buf[end] = '\0';
		if ((lstat(buf, &tmp)) == -1)
			return (-1);
		if (S_ISDIR(tmp.st_mode))
			return (2);
		else
			return (3);
	}
	else
	{
		if (S_ISDIR(tmp.st_mode))
			return (1);
		else
			return (0);
	}
}

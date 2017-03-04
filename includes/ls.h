/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 00:38:31 by vrybalko          #+#    #+#             */
/*   Updated: 2017/03/05 01:01:17 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _LS_H
# define _LS_H

#include <sys/types.h>
#include <dirent.h>
/*
struct				group
{
	char			*gr_name;
	char			*gr_passwd;
	gid_t			gr_gid;
	char			**gr_mem;
};

struct				dirent
{
	ino_t			d_ino;
	off_t			d_off;
	unsigned char	d_reclen;
	unsigned char	d_type;
	char			d_name[256];
};
*/

typedef struct		s_fl
{
	int				list;
	int				rec;
	int				rev;
	int				all;
	int				time;
}					t_fl;

typedef struct		s_e
{
	t_fl			fl;
}					t_e;

void		check_arg(t_e *e, char *);

#endif

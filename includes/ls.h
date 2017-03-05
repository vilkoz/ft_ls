/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 00:38:31 by vrybalko          #+#    #+#             */
/*   Updated: 2017/03/05 19:22:41 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _LS_H
# define _LS_H

# include "../libft/libft.h"
# include <sys/types.h>
# include <dirent.h>
# include <sys/stat.h>
# include <stdio.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>

/*
** struct				dirent
** {
**	ino_t			d_ino;
**	off_t			d_off;
**	unsigned char	d_reclen;
**	unsigned char	d_type;
**	char			d_name[256];
** };
*/

typedef struct stat		t_stat;
typedef struct passwd	t_passwd;
typedef struct group	t_group;

typedef struct			s_fl
{
	int					list;
	int					rec;
	int					rev;
	int					all;
	int					time;
}						t_fl;

typedef struct			s_e
{
	t_fl				fl;
}						t_e;

void					check_arg(t_e *e, char *arg);
void					read_arg(t_e *e, char *arg);

#endif

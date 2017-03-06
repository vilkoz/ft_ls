/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 00:38:31 by vrybalko          #+#    #+#             */
/*   Updated: 2017/03/06 03:23:23 by vrybalko         ###   ########.fr       */
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
typedef struct dirent	t_dirent;

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
	int					va;
	t_list				*lst;
}						t_e;

typedef struct			s_arg
{
	t_stat				*stat;
	char				*rights;
	char				*nlinks;
	char				*user;
	char				*group;
	char				*size;
	char				*time;
	char				*name;
}						t_arg;

void					check_arg(t_e *e, char *arg);
void					read_arg(t_e *e, char *arg);
void					open_dir(t_e *e, char *arg);
t_arg					*stat_format(t_e *e, char *arg);
void					ft_sort(t_e *e);
int						is_folder(char *arg);

#endif

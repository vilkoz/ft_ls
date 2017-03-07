/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 00:38:31 by vrybalko          #+#    #+#             */
/*   Updated: 2017/03/07 16:39:31 by vrybalko         ###   ########.fr       */
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
# define LEFT 23
# define RIGHT 24
# define ABS(x) (((x) < 0) ? -(x) : (x))

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

typedef struct			s_len
{
	size_t				rights;
	size_t				nlinks;
	size_t				user;
	size_t				group;
	size_t				size;
	size_t				time;
	quad_t				blocks;
	t_fl				fl;
}						t_len;

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
void					open_dir(t_e *e, char *arg, t_list **lst);
t_arg					*stat_format(t_e *e, char *arg);
void					ft_sort(t_e *e);
int						is_folder(char *arg);
void					read_rec_dir(t_e *e, char *arg);
void					print_list(t_e *e);
char					*ft_fj(char *s1, char *s2);
char					*ft_fsub(char *s, size_t start, size_t end);

#endif

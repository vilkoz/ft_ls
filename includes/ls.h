/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 00:38:31 by vrybalko          #+#    #+#             */
/*   Updated: 2017/03/10 17:12:18 by vrybalko         ###   ########.fr       */
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
# ifndef ABS
#  define ABS(x) (((x) < 0) ? -(x) : (x))
# endif
# define SIXMONTH ((365 / 2) * 86400)

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
	int					ret;
	int					print_dir_name;
	int					arg_conunt;
	int					arg_num;
	int					was_solo;
}						t_e;

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
	t_e					*e;
}						t_len;

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
	char				*targ_link;
	int					is_solo;
}						t_arg;

/*
** ft_check_arg.c
*/

void					check_arg(t_e *e, char *arg);
int						is_arg_flag(char *arg);
int						is_flag(char c);

void					read_arg(t_e *e, char *arg);
void					open_dir(t_e *e, char *arg, t_list **lst);
int						is_folder(char *arg);
void					read_rec_dir(t_e *e, char *arg);
char					*ft_fj(char *s1, char *s2);
char					*ft_fsub(char *s, size_t start, size_t end);
void					ft_sort(t_e *e, t_list *head);
void					print_list(t_e *e, t_list *head);
t_arg					*stat_format(t_e *e, char **arg);
void					init_len(t_len *len, t_e *e);
void					recursive(t_list *l1, t_len *len);
void					lst_clear(void *a1, size_t size);
int						is_hidden(char *name);

/*
** fillers.c
*/

void					print_type(t_stat el, t_arg *a);
void					print_rights(t_stat el, t_arg *a);
void					print_nlink(t_stat el, t_arg *a);
void					print_user(t_stat el, t_arg *a);

/*
** fillers1.c
*/

char					*format_line(char *major, char *minor);
void					print_size(t_stat el, t_arg *a);
void					print_time(t_stat el, t_arg *a);

/*
** list_tools.c
*/
void					lst_iter_len(t_list *lst,
									void (*f)(t_list *l1, t_len *len),
									t_len *len);
void					count_len(t_list *l, t_len *len);
void					init_len(t_len *len, t_e *e);

#endif

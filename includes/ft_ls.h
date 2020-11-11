/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgamora <cgamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 13:45:55 by cgamora           #+#    #+#             */
/*   Updated: 2020/11/11 10:48:51 by cgamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "../libft/libft.h"
# include "../libft/get_next_line.h"
# include "../libft/ft_printf/ft_printf.h"
# include <unistd.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <pwd.h>
# include <grp.h>
# include <sys/xattr.h>
# include <time.h>
# include <errno.h>
# include <sys/ioctl.h>
# include <sys/acl.h>

# define MAX(x, y) x > y ? x : y

typedef struct dirent   t_dirent;
typedef struct stat     t_stat;
typedef struct group    t_group;
typedef struct passwd	t_passwd;
typedef struct winsize	t_winsize;

typedef struct      s_flags
{
    int             l;
    int             R;
    int             a;
    int             r;
    int             t;
}                   t_flags;

typedef struct		s_info
{
	char			*name;
	char			*path;
	struct stat		info;
	int				dir;
	int				total;
	struct s_info	*next;
}					t_info;

typedef struct		s_flagl
{
	int			nlink;
	int			pw_name;
	int			gr_name;
	int			st_size;
	int			major;
	int			minor;
	int			device;
	int			f_name;
	int			w_cols;
}					t_flagl;


//global

int             g_parser;

//parse

int				parse_to_struct(t_flags *flag, int argc, char **argv);
int				ft_start_ls(char *dir_name, t_flags *flag);
int				add_file(t_info *info_list, char *fd_name);
int				dir_list(t_info *info_list, char *fd_name, t_flags *flag);
int				timecmp(t_info *a, t_info *b, t_flags *flag);
void			list_sort(t_info *tmp_list, t_flags *flag);
t_info			*ascii_sort(t_info *a, t_info *b, t_flags *flag);
t_flagl			get_flagl(t_info *tmp_list);
int				get_termcolom(void);
int				print_all(t_info *info_list, t_flagl infrml, t_flags *flag);
void			print_list(t_info *info_list, t_flagl informl, t_flags *flag);
void			print_permissions(t_info *info_list);

#endif
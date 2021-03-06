/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgamora <cgamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 09:41:14 by cgamora           #+#    #+#             */
/*   Updated: 2020/11/11 10:48:25 by cgamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	print_link(t_info *a)
{
	char	buf[2048];

	ft_bzero(buf, 2048);
	readlink(a->path, buf, 2047);
	ft_printf(" -> %s", buf);
}

void	print_date(t_info *a, t_flags *flag)
{
	write(1, &ctime(&a->info.st_mtime)[4], 12);
	ft_putchar(' ');
}

void	print_name(t_info *list, int size)
{
	if (size)
		ft_printf("%-*s ", size, list->name);
	else
		ft_putstr(list->name);
}

void		print_type(t_info *info_list)
{
	if (S_ISREG(info_list->info.st_mode))
		ft_putchar('-');
	else if (S_ISDIR(info_list->info.st_mode))
		ft_putchar('d');
	else if (S_ISBLK(info_list->info.st_mode))
		ft_putchar('b');
	else if (S_ISCHR(info_list->info.st_mode))
		ft_putchar('c');
	else if (S_ISFIFO(info_list->info.st_mode))
		ft_putchar('p');
	else if (S_ISLNK(info_list->info.st_mode))
		ft_putchar('l');
	else if (S_ISSOCK(info_list->info.st_mode))
		ft_putchar('s');
	else
		ft_putchar('?');
}

void		print_list(t_info *info_list, t_flagl informl, t_flags *flag)
{
	if (flag->l)
	{
		print_type(info_list);
		print_permissions(info_list);
		ft_printf(" %*d ", informl.nlink, info_list->info.st_nlink);
		ft_printf("%-*s  ", informl.pw_name, getpwuid(info_list->info.st_uid)->pw_name);
		ft_printf("%-*s ", informl.gr_name, getgrgid(info_list->info.st_gid)->gr_name);
		if (S_ISBLK(info_list->info.st_mode) || S_ISCHR(info_list->info.st_mode))
		{
			if (informl.st_size > informl.major + informl.minor)
				ft_printf("%*s", informl.st_size - informl.major - informl.minor - 2, "");
			ft_printf(" %*d, %*d ", informl.major, major(info_list->info.st_rdev),
									informl.minor, minor(info_list->info.st_rdev));
		}
		else
			ft_printf(" %*d ", informl.st_size, info_list->info.st_size);
		print_date(info_list, flag);
		print_name(info_list, 0);
		(S_ISLNK(info_list->info.st_mode)) ? print_link(info_list) : 0;
	}
	else
		print_name(info_list, informl.f_name + 5);
}
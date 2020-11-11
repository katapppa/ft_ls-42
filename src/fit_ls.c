/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fit_ls.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgamora <cgamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 01:44:08 by cgamora           #+#    #+#             */
/*   Updated: 2020/11/11 11:01:47 by cgamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int			ft_isdir(char *fd_name)
{
	t_stat		stata;

	if (stat(fd_name, &stata) != 0)
		return (0);
	return (S_ISDIR(stata.st_mode));
}

int			count_name(char *fd_name)
{
	int i;

	i = 0;
	while (fd_name[i] && (fd_name[i] == '.' || fd_name[i] == '/'))
		i++;
	return (i);
}

int			check_file(char *fd_name, t_flags *flag, t_info *info_list)
{
	DIR		*dir;
	int		i;

	errno = 0;
	i = count_name(fd_name);
	if (!(dir = opendir(fd_name)))
	{
		if (errno == 2)
			ft_printf("ft_ls: %s: %s\n", fd_name, strerror(errno));
		else if (errno == 13 && ft_isdir(fd_name))
			ft_printf("ft_ls: %s: %s\n", fd_name, strerror(errno));
		else
			add_file(info_list, fd_name);
		return (1);
	}
	return (0);
}

int			ft_start_ls(char *fd_name, t_flags *flag)
{
	t_info		*info_list;
	t_info		*tmp_list;
	t_flagl		infrml;
	int			total;

	tmp_list = NULL;
	if (!(info_list = (t_info*)malloc(sizeof(t_info)))) //мне лень писать ошибку
		exit(1);
	if (check_file(fd_name, flag, info_list) == 1)
		return (0);
	total = dir_list(info_list, fd_name, flag);
	list_sort(tmp_list, flag);
	if (tmp_list && flag->l)
		ft_printf("total %d\n", total);
	info_list = tmp_list;
	infrml = get_flagl(tmp_list); //yes +
	print_all(info_list, infrml, flag); //yes + (no work)
	free(info_list);
	return (1);
}

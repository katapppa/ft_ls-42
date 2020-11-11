/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_getter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgamora <cgamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 04:18:32 by cgamora           #+#    #+#             */
/*   Updated: 2020/11/11 06:43:51 by cgamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void		next_list(t_info *info_list, t_info *tmp)
{
	tmp->next = info_list;
	info_list = tmp;
}

char		*control_path(char *fd_name, char *dir_name)
{
	char *tmp;
	char *tmp_two;

	if (!dir_name)
	{
		if (fd_name[0] == '~' || fd_name[0] == '.' || fd_name[0] == '/')
			return (ft_strdup(fd_name));
		return (ft_strjoin("./", fd_name));
	}
	tmp = ft_strjoin(fd_name, "/");
	tmp_two = ft_strjoin(tmp, dir_name);
	free(tmp);
	return (tmp_two);
}

int			add_direct(t_info *info_list, char *fd_name, t_dirent *direct)
{
	t_info	*tmp;

	if (!(tmp = (t_info*)malloc(sizeof(t_info))))
		exit(1);
	tmp->name = ft_strdup(fd_name);
	tmp->path = control_path(fd_name, direct->d_name);
	if (lstat(tmp->path, &(tmp->info)) == -1)
	{
		ft_printf("dir_ft_ls:");
		//perror(fd_name);
		free(tmp);
		return (0);
	}
	if (S_ISDIR(tmp->info.st_mode) == 1)
		tmp->dir = 1;
	next_list(info_list, tmp);
	return (tmp->info.st_blocks);
}

int			dir_list(t_info *info_list, char *fd_name, t_flags *flag)
{
	DIR			*dir;
	t_dirent	*direct;
	int			total;

	total = 0;
	dir = opendir(fd_name);
	while ((direct = readdir(dir)) != NULL)
	{
		if (direct->d_name[0] != '.' || flag->a)
			total += add_direct(info_list, fd_name, direct);
	}
	closedir(dir);
	return (total);
}

int			add_file(t_info *info_list, char *fd_name)
{
	t_info	*tmp;

	if (!(tmp = (t_info*)malloc(sizeof(t_info))))
		exit(1);
	tmp->name = ft_strdup(fd_name);
	tmp->path = ft_strdup(fd_name);
	if (lstat(tmp->path, &(tmp->info)) == -1)
	{
		ft_printf("file_ft_ls:");
		perror(tmp->path);
		free(tmp);
		return (0);
	}
	tmp->dir = 0;
	next_list(info_list, tmp);
	return (tmp->info.st_blocks);
}

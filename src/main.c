/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgamora <cgamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 13:42:57 by cgamora           #+#    #+#             */
/*   Updated: 2020/11/09 19:25:23 by cgamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void    ft_direc_error(char *s)
{
    printf("ls: %s: No such file or directory\n", s);
    exit(1);
}

void    ft_flag_error(char **argv, int i)
{
    if (argv[1][i] == '-')
        ft_direc_error(&argv[1][i]);
    ft_printf("No flag %c\n", argv[1][i]);
    exit(1);
}

int     parse_to_struct(t_flags *flag, int argc, char **argv)
{
    int i;

    i = 1;
    if (argv[1] && argv[1][0] == '-')
    {
        while (argv[1][i])
        {
            if (argv[1][i] == 'l')
                flag->l = 1;
            else if (argv[1][i] == 'a')
                flag->a = 1;
            else if (argv[1][i] == 'R')
                flag->R = 1;
            else if (argv[1][i] == 'r')
                flag->r = 1;
            else if (argv[1][i] == 't')
                flag->t = 1;
            else
                ft_flag_error(argv, i);
            i++;
        }
    }
    return (1);
}

t_flags    *memory_strfl(t_flags *flag)
{
    if (!(flag = (t_flags*)malloc(sizeof(t_flags))))
        exit(1);
    flag->a = 0;
    flag->l = 0;
    flag->R = 0;
    flag->r = 0;
    flag->t = 0;
    return (flag);
}

int     main(int argc, char **argv)
{
    t_flags *flag;
    DIR     *folder;
	struct dirent	*first;

    flag = memory_strfl(flag);
    parse_to_struct(flag, argc, argv);
    ft_printf("%d and %d and %d and %d and %d\n", flag->a, flag->l, flag->R, flag->r, flag->t);

    folder = opendir(".");
	first = readdir(folder);
	struct stat stet;
	lstat(".", &stet);
    return 1;
}

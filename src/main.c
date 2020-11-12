/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgamora <cgamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 13:42:57 by cgamora           #+#    #+#             */
/*   Updated: 2020/11/12 15:13:34 by cgamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"


int			print_file(int argc, char **argv, t_flags *flag)
{
	int		i;
	int		g_amount;
	t_info	*info;
	t_flagl flagl;

	info = NULL;
	i = g_parser;
	g_amount = 0;
	while (i < argc)
	{
		errno = 0;
		if (!ft_isdir(argv[i]))
		{
			add_file(info, argv[i]);
			if (errno != 2)
				g_amount++;
			else
				g_amount = 0;
		}
		i++;
	}
	list_sort(info, flag);
	flagl = get_flagl(info);
	i = print_all(info, flagl, flag);
	if (i > 1)
		ft_printf("\n");
	return (g_amount);

}

void		print_dir(int argc, char **argv, t_flags *flag)
{
	char 	*path;
	int 	first_dir;

	while (g_parser < argc)
	{
		if (ft_isdir(argv[g_parser]))
		{
			if (g_amount && !first_dir)
			{
				ft_printf("\n\n");
				g_amount = 0;
			}
			first_dir = 1;
			if (first_dir == 1)
				ft_printf("\n");
			ft_printf("%s:\n", argv[g_parser]);
			path = control_path(argv[g_parser], NULL);
			ft_start_ls(path, flag);
			if (g_parser + 1 < argc)
				ft_printf("\n");
			if (g_parser + 1 == argc)
				ft_printf("\n");
			free(path);
		}
		g_parser++;
	}
}

t_flags		*memory_strfl(t_flags *flag)
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

int			main(int argc, char **argv)
{
	t_flags			*flag;

	flag = memory_strfl(flag);
	parse_to_struct(flag, argc, argv);
	ft_printf("PARSER: %d\n", g_parser);
	ft_printf("ARGC: %d\n", argc);
	// ft_printf("%d and %d and %d and %d and %d\n", flag->a, flag->l, flag->R, flag->r, flag->t);
	if (g_parser == argc)
	{
		ft_start_ls(".", flag);
	}
	 else if (g_parser + 1 == argc)
	 {
	 	print_file(argc, argv, flag);
	 	if (errno != 2 && ft_start_ls(argv[g_parser], flag ))
		{
			ft_putchar('\n');
		}
	 }
	 else
	 {
		sort_av(argc, &argv, g_parser, flag);
		g_amount = print_file(argc, argv, flag);
		print_dir(argc, argv, flag);
		if (flag->l && (g_parser + 1 < argc))
			ft_putchar('\n');
	 }
	free(flag);
	return (1);
}

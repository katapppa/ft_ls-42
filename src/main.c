/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgamora <cgamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 13:42:57 by cgamora           #+#    #+#             */
/*   Updated: 2020/11/11 07:19:42 by cgamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

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
	// else if (g_parser + 1 == argc)
	// {

	// }
	// else
	// {
		
	// }
	free(flag);
	return (1);
}

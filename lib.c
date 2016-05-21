/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thifranc <thifranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/20 15:42:06 by thifranc          #+#    #+#             */
/*   Updated: 2016/05/22 00:07:46 by thifranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void	use_termcap(char *cmd)
{
	char	*out;

	out = tgetstr(cmd, NULL);
	ft_putstr(out);
}

void	color_with_type(mode_t st_mode)
{
	if (S_ISBLK(st_mode))
		ft_putstr(RESET);
	else if (S_ISCHR(st_mode))
		ft_putstr(GREEN);
	else if (S_ISDIR(st_mode))
		ft_putstr(YELLOW);
	else if (S_ISLNK(st_mode))
		ft_putstr(RED);
	else if (S_ISSOCK(st_mode))
		ft_putstr(MAGENTA);
	else if (S_ISFIFO(st_mode))
		ft_putstr(CYAN);
	else if (S_ISREG(st_mode))
		ft_putstr(BLUE);
}

void	exiting(char *msg)
{
	ft_putstr(msg);
	exit(-1);
}

void	whipe_me(void)
{
	use_termcap("cl");
	use_termcap("ho");
	use_termcap("vi");
}

t_list	*arg_in_list(int ac, char **av)
{
	t_list	*head;
	int		i;

	i = 1;
	head = NULL;
	while (i < ac)
	{
		add_node(&head, av[i]);
		i++;
	}
	circle_list(head);
	return (head);
}

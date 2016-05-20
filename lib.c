/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thifranc <thifranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/20 15:42:06 by thifranc          #+#    #+#             */
/*   Updated: 2016/05/20 18:07:31 by thifranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void	use_termcap(char *cmd)
{
	char	*out;

	out = tgetstr(cmd, NULL);
	ft_putstr(out);
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

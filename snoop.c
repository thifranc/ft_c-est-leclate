/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   snoop.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thifranc <thifranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/20 15:51:47 by thifranc          #+#    #+#             */
/*   Updated: 2016/05/22 00:17:02 by thifranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void	set_termios(struct termios *old)
{
	struct termios	new;

	new = *old;
	new.c_lflag &= ~(ICANON | ECHO);
	new.c_cc[VMIN] = 1;
	new.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &new);
}

t_list	*look_for_cur(t_list *head)
{
	t_list	*out;

	out = head;
	while (!out->cur)
		out = out->next;
	return (out);
}

void	node_out(t_list **a, t_list **head)
{
	t_list	*tmp;

	if ((*a) == (*a)->next)
		delnode(&(*head));
	else
	{
		(*a)->prev->next = (*a)->next;
		(*a)->next->prev = (*a)->prev;
		tmp = *a;
		if (*a == *head)
			(*head) = (*head)->next;
		go_next(*a);
		delnode(&tmp);
	}
}

void	do_cmd(char c[8], t_list **head, struct termios *old)
{
	t_list	*cur;

	cur = look_for_cur(*head);
	if ((c[0] == 27 && c[1] == 91 && c[2] == 51 && c[3] == 126)
			|| (c[0] == 127 && !c[1] && !c[2]))
		node_out(&cur, &(*head));
	else if ((c[0] == 27 && c[1] == 91 && c[2] == 68) ||
			(c[0] == 27 && c[1] == 91 && c[2] == 65))
		go_prev(cur);
	else if ((c[0] == 27 && c[1] == 91 && c[2] == 67) ||
			(c[0] == 27 && c[1] == 91 && c[2] == 66))
		go_next(cur);
	else if (c[0] == 27 && !c[1] && !c[2])
		do_bye(NULL, old);
	else if (c[0] == 32 && !c[1] && !c[2])
		select_arg(cur);
	else if (c[0] == 10 && !c[1] && !c[2])
		do_bye(*head, old);
	if (!*head)
		do_bye(NULL, old);
}

void	snoop_key(t_list *src, struct termios *old)
{
	static t_list	*head;
	char			buf[8];

	if (src)
		head = src;
	if (!src)
		return (print_list(head));
	ft_bzero(buf, 8);
	print_list(head);
	while (read(0, buf, 8) != 0)
	{
		do_cmd(buf, &head, old);
		ft_bzero(buf, 8);
		print_list(head);
	}
}

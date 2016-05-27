/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thifranc <thifranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/18 09:37:22 by thifranc          #+#    #+#             */
/*   Updated: 2016/05/27 18:31:31 by thifranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

/*
**data : 0=width & 1=lines & 2=flag & 3=size & 4=longest word
*/

void	return_list(t_list *head)
{
	t_list	*tmp;
	int		size;

	size = crl_list_size(head);
	whipe_me();
	tmp = head;
	while (size)
	{
		if (tmp->opt & SELECTED)
			print_elem(*tmp, 0);
		if (tmp->opt & SELECTED)
			write(1, " ", 1);
		size--;
		tmp = tmp->next;
	}
}

void	get_data(int data[5], t_list *head)
{
	t_list			*tmp;
	int				size;
	struct winsize	new;

	tmp = head;
	ioctl(0, TIOCGWINSZ, &new);
	data[0] = new.ws_col;
	data[1] = new.ws_row;
	data[3] = crl_list_size(head);
	size = data[3];
	data[4] = 0;
	while (size)
	{
		if ((int)ft_strlen(tmp->data) > data[4])
			data[4] = ft_strlen(tmp->data);
		tmp = tmp->next;
		size--;
	}
	data[2] = data[3] / (data[0] / (data[4] + 1));
}

void	print_elem(t_list elem, int type)
{
	struct stat	stats;

	if (type && lstat(elem.data, &stats) != -1)
		color_with_type(stats.st_mode);
	if (type && elem.opt)
		use_termcap("mr");
	if (type && elem.cur)
		use_termcap("us");
	ft_putstr(elem.data);
	use_termcap("me");
}

void	print_list(t_list *head)
{
	t_list	*tmp;
	int		max;
	int		data[5];

	whipe_me();
	get_data(data, head);
	if (data[2] >= data[1] || data[0] < data[4])
		return (ft_putstr("Window too small !\n"));
	tmp = head;
	while (data[3])
	{
		max = data[0] / (data[4] + 1);
		while (max && data[3])
		{
			print_elem(*tmp, 1);
			write(1, " ", 1);
			ft_print_n_char(' ', data[4] - ft_strlen(tmp->data));
			max--;
			tmp = tmp->next;
			data[3]--;
		}
		write(1, "\n", 1);
	}
}

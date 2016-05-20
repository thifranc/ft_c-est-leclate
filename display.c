/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thifranc <thifranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/18 09:37:22 by thifranc          #+#    #+#             */
/*   Updated: 2016/05/20 17:57:10 by thifranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

/*
**data : 0=width & 1=lines & 2=flag & 3=size & 4=longest word
*/

int		width_to_line(t_list *head)
{
	t_list			*tmp;
	struct winsize	win;
	int				m;
	int				list_size;
	int				ct;

	tmp = head;
	ioctl(0, TIOCGWINSZ, &win);
	if (!head)
		return ((19 + 1) / win.ws_col + 1);
	list_size = crl_list_size(tmp);
	ct = 0;
	m = 0;
	while (list_size)
	{
		m += ft_strlen(tmp->data) + 1;
		list_size--;
		if ((m - (win.ws_col)) > 1 || (m - win.ws_col == 1 && list_size))
		{
			ct++;
			m - win.ws_col == 1 ? m *= 0 : (m = ft_strlen(tmp->data) + 1);
		}
		tmp = tmp->next;
	}
	return (ct + 1);
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
	data[2] = width_to_line(head);
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
}

void	print_elem(t_list elem)
{
	//put color related to file type with stat (if fail then isn't file)
	if (elem.opt)
		ft_putstr("\033[7m");//termcap mr
	if (elem.cur)
		use_termcap("us");
	ft_putstr(elem.data);
	if (elem.opt)//termcap me
		ft_putstr("\033[m");
	if (elem.cur)
		use_termcap("ue");
}

void	print_list(t_list *head)
{
	t_list	*tmp;
	int		max;
	int		data[5];

	whipe_me();
	get_data(data, head);
	if (data[2] >= data[1] || data[0] < data[4])
		write(1, "Window too small !\n", 19);
	tmp = head;
	max = 0;
	while (data[3])
	{
		max += ft_strlen(tmp->data) + 1;
		if (max - data[0] >= 1)
		{
			if (max - data[0] > 1)
				write(1, "\n", 1);
			max - data[0] == 1 ? max *= 0 : (max = ft_strlen(tmp->data) + 1);
		}
		print_elem(*tmp);
		tmp = tmp->next;
		data[3]--;
		if (data[3] && max - data[0] != 1)
			write(1, " ", 1);
	}
}

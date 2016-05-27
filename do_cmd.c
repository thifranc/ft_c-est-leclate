/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thifranc <thifranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/20 16:20:23 by thifranc          #+#    #+#             */
/*   Updated: 2016/05/27 17:35:21 by thifranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void	go_prev(t_list *cur)
{
	cur->cur = 0;
	cur->prev->cur = 1;
}

void	go_next(t_list *cur)
{
	cur->cur = 0;
	cur->next->cur = 1;
}

void	go_down(t_list *cur)
{
	int		data[5];
	int		jump;

	get_data(data, cur);
	jump = data[0] / (data[4] + 1);
	while (jump)
	{
		go_next(cur);
		cur = cur->next;
		jump--;
	}
}

void	go_up(t_list *cur)
{
	int		data[5];
	int		jump;

	get_data(data, cur);
	jump = data[0] / (data[4] + 1);
	while (jump)
	{
		go_prev(cur);
		cur = cur->prev;
		jump--;
	}
}

void	select_arg(t_list *cur)
{
	cur->opt ^= SELECTED;
	go_next(cur);
}

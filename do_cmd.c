/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thifranc <thifranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/20 16:20:23 by thifranc          #+#    #+#             */
/*   Updated: 2016/05/20 17:52:29 by thifranc         ###   ########.fr       */
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

void	select_arg(t_list *cur)
{
	cur->opt ^= SELECTED;
	go_next(cur);
}

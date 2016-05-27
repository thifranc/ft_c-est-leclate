/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thifranc <thifranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/10 15:49:51 by thifranc          #+#    #+#             */
/*   Updated: 2016/05/24 17:57:19 by thifranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

t_list	*new_node(char *data)
{
	t_list	*new;

	if (!(new = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	new->next = NULL;
	new->prev = NULL;
	new->opt = 0;
	new->cur = 0;
	new->data = ft_strdup(data);
	return (new);
}

void	add_node(t_list **list, char *data)
{
	if (!(*list))
		(*list) = new_node(data);
	else if (!(*list)->next)
	{
		(*list)->next = new_node(data);
		((*list)->next)->prev = (*list);
	}
	else
		add_node(&(*list)->next, data);
}

void	delnode(t_list **tmp)
{
	free((*tmp)->data);
	free(*tmp);
	*tmp = NULL;
}

void	circle_list(t_list *list)
{
	t_list	*tmp;

	tmp = list;
	if (!list)
		return ;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = list;
	list->prev = tmp;
}

int		crl_list_size(t_list *head)
{
	t_list	*first;
	t_list	*tmp;
	int		out;

	if (!head)
		return (0);
	out = 1;
	first = head;
	tmp = head;
	tmp = tmp->next;
	while (first != tmp)
	{
		tmp = tmp->next;
		out++;
	}
	return (out);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thifranc <thifranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/15 13:30:32 by thifranc          #+#    #+#             */
/*   Updated: 2016/05/20 18:05:16 by thifranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALL_H
# define ALL_H

# include <curses.h>
# include <signal.h>
# include <term.h>
# include <unistd.h>
# include <termios.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/ioctl.h>
# include "libft/libft.h"

# define SELECTED 1

typedef struct		s_list
{
	struct s_list	*next;
	struct s_list	*prev;
	char			*data;
	int				opt;
	int				cur;
}					t_list;

void	exiting(char *msg);
void	whipe_me(void);
void	use_termcap(char *cmd);

void	wild_cases(int ac, struct termios *old);
void	signalhandle(int sig);
void	snoop_signal(void);

void	set_termios(struct termios *old);
void	snoop_key(t_list *src, struct termios *old);
void	do_cmd(char c[8], t_list *head, struct termios *old);

void	go_prev(t_list *cur);
void	select_arg(t_list *cur);
void	go_next(t_list *cur);
void	do_bye(t_list *head, struct termios *old);

void	get_data(int data[5], t_list *head);
void	print_list(t_list *head);
void	print_elem(t_list elem);
int		width_to_line(t_list *head);

void	add_node(t_list **list, char *data);
t_list	*arg_in_list(int ac, char **av);
int		crl_list_size(t_list *head);
void	circle_list(t_list *list);
t_list	*new_node(char *datta);
void	node_out(t_list **a, t_list **head);
void	delnode(t_list **tmp);
#endif

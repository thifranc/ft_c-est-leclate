/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thifranc <thifranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/15 13:30:32 by thifranc          #+#    #+#             */
/*   Updated: 2016/05/27 18:31:44 by thifranc         ###   ########.fr       */
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
# include <sys/stat.h>
# include "libft/libft.h"

# define RED     "\x1b[31m"
# define GREEN   "\x1b[32m"
# define YELLOW  "\x1b[33m"
# define BLUE    "\x1b[34m"
# define MAGENTA "\x1b[35m"
# define CYAN    "\x1b[36m"
# define RESET   "\x1b[0m"

# define SELECTED 1
# define INIT 666

typedef struct		s_list
{
	struct s_list	*next;
	struct s_list	*prev;
	char			*data;
	int				opt;
	int				cur;
}					t_list;

void				exiting(char *msg);
void				whipe_me(void);
void				use_termcap(char *cmd);

void				wild_cases(int ac, struct termios *old);
void				signalhandle(int sig);
void				snoop_signal(void);

void				set_termios(struct termios *old);
void				snoop_key(t_list *src, struct termios *old);
void				do_cmd(char c[8], t_list **head, struct termios *old);
void				return_list(t_list *head);

void				go_prev(t_list *cur);
void				select_arg(t_list *cur);
void				go_next(t_list *cur);
void				go_up(t_list *cur);
void				go_down(t_list *cur);
void				do_bye(t_list *head, struct termios *old);

void				get_data(int data[5], t_list *head);
void				print_list(t_list *head);
void				print_elem(t_list elem, int type);
void				color_with_type(mode_t stats);

void				add_node(t_list **list, char *data);
t_list				*arg_in_list(int ac, char **av);
int					crl_list_size(t_list *head);
void				circle_list(t_list *list);
t_list				*new_node(char *datta);
void				node_out(t_list **a, t_list **head);
void				delnode(t_list **tmp);
#endif

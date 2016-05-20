/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thifranc <thifranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/20 13:15:12 by thifranc          #+#    #+#             */
/*   Updated: 2016/05/20 18:07:40 by thifranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void	do_bye(t_list *head, struct termios *old)
{
	if (head)
		print_list(head);
	tcsetattr(0, TCSANOW, old);//simple ou double pointeur ???
	exit(-1);
}

void	wild_cases(int args, struct termios *back)
{
	if (args <= 1)
		exiting("No args\n");
	if (getenv("TERM") == NULL)
		exiting("Var TERM could not be found\n");
	if (tgetent(NULL, getenv("TERM")) == -1)
		exiting("Database could not be found\n");
	if (tcgetattr(0, back) == -1)
		exiting("Data could not be loaded into termios\n");
}

void	signalhandle(int sig)
{
	static struct termios	backup;

	if (sig == 0)
		tcgetattr(0, &backup);
	if (sig == SIGCONT)
	{
		set_termios(&backup);
		snoop_key(NULL, &backup);
	}
	if (sig == SIGWINCH)
		snoop_key(NULL, &backup);
	else
		do_bye(NULL, &backup);
}

void	snoop_signal(void)
{
	signal(SIGINT, signalhandle);
	signal(SIGKILL, signalhandle);
	signal(SIGQUIT, signalhandle);
	signal(SIGWINCH, signalhandle);
	signal(SIGCONT, signalhandle);
}

int		main(int ac, char **av)
{
	struct termios	old;
	t_list			*head;

	wild_cases(ac, &old);
	head = arg_in_list(ac, av);
	signalhandle(0);
	snoop_signal();
	set_termios(&old);
	snoop_key(head, &old);//pb adress ptr
}

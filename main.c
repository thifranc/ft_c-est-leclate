/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thifranc <thifranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/20 13:15:12 by thifranc          #+#    #+#             */
/*   Updated: 2016/05/22 00:35:00 by thifranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void	do_bye(t_list *head, struct termios *old)
{
	t_list	*tmp;
	int		size;

	if (head)
	{
		tmp = head;
		size = crl_list_size(tmp);
		while (size)
		{
			if (tmp->cur)
				tmp->cur = 0;
			tmp = tmp->next;
			size--;
		}
		return_list(head);
	}
	else
		whipe_me();
	use_termcap("ve");
	tcsetattr(0, TCSANOW, old);
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
	char					stop[2];

	if (sig == INIT)
		tcgetattr(0, &backup);
	else if (sig == SIGCONT)
	{
		signal(SIGTSTP, signalhandle);
		set_termios(&backup);
		signal(SIGCONT, signalhandle);
		snoop_key(NULL, &backup);
	}
	else if (sig == SIGWINCH)
		snoop_key(NULL, &backup);
	else if (sig == SIGTSTP)
	{
		stop[0] = backup.c_cc[VSUSP];
		stop[1] = 0;
		use_termcap("ve");
		tcsetattr(0, TCSANOW, &backup);
		signal(SIGTSTP, SIG_DFL);
		ioctl(0, TIOCSTI, stop);
	}
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
	signal(SIGTSTP, signalhandle);
}

int		main(int ac, char **av)
{
	struct termios	old;
	t_list			*head;

	wild_cases(ac, &old);
	head = arg_in_list(ac, av);
	signalhandle(INIT);
	set_termios(&old);
	snoop_signal();
	snoop_key(head, &old);
}

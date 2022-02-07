/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spzona <spzona@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 16:19:13 by spzona            #+#    #+#             */
/*   Updated: 2022/02/03 13:24:59 by spzona           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

static t_message	g_mes;

static void	ft_server_answer(int signal, siginfo_t *info, void *context)
{
	(void)context;
	(void)signal;
	(void)info;
	write(1, "Successfully sent!\n", 19);
	exit(EXIT_SUCCESS);
}

static void	ft_bit_sender(int signal, siginfo_t *info, void *context)
{
	int	bit;

	(void)context;
	(void)signal;
	bit = ((g_mes.str[g_mes.str_position]) >> (7 - g_mes.bit_position)) & 1;
	usleep(USLEEP);
	if (bit == 0)
		kill((*info).si_pid, SIGUSR1);
	else
		kill((*info).si_pid, SIGUSR2);
	++(g_mes.bit_position);
	if (g_mes.bit_position == 8)
	{
		g_mes.bit_position = 0;
		++(g_mes.str_position);
	}
}

static void	fr_message_sender(int server_pid)
{
	struct sigaction	sigusr2_handler;
	struct sigaction	sigusr1_handler;
	siginfo_t			info;

	sigusr1_handler.sa_sigaction = ft_bit_sender;
	sigusr1_handler.sa_flags = SA_SIGINFO;
	sigusr2_handler.sa_sigaction = ft_server_answer;
	sigusr2_handler.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sigusr1_handler, NULL);
	sigaction(SIGUSR2, &sigusr2_handler, NULL);
	info.si_pid = server_pid;
	ft_bit_sender(SIGUSR1, &info, NULL);
	while (1)
		pause();
}

int	main(int argc, char **argv)
{
	if (argc == 3)
	{
		g_mes.str = argv[2];
		fr_message_sender(ft_atoi(argv[1]));
	}
	else
		write(1, "Usage: ./client [SERVER_PID] [MESSAGE]\n", 40);
	return (0);
}

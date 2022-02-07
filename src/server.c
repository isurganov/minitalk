/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spzona <spzona@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 15:43:14 by spzona            #+#    #+#             */
/*   Updated: 2022/02/03 13:25:00 by spzona           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

static t_message	g_mes;

static void	ft_init_message(t_message *message)
{
	int	i;

	i = 0;
	(*message).is_sending = 1;
	(*message).str_position = 0;
	(*message).bit_position = 0;
	while (i < BUFFER)
	{
		(*message).str[i] = '\0';
		++i;
	}
}

static void	ft_message_printer(void)
{
	int	i;

	write(1, g_mes.str, g_mes.str_position);
	i = 0;
	while (i < g_mes.str_position)
	{
		g_mes.str[i] = '\0';
		++i;
	}
	g_mes.str_position = 0;
}

static void	ft_bit_receiver(int signal, siginfo_t *info, void *context)
{
	int	bit;

	(void)context;
	if (signal == SIGUSR1)
		bit = 0;
	else
		bit = 1;
	g_mes.str[g_mes.str_position] |= (bit << (7 - g_mes.bit_position));
	if (++(g_mes.bit_position) == 8)
	{
		if (g_mes.str[g_mes.str_position] == '\0')
		{
			g_mes.is_sending = 0;
			ft_message_printer();
			kill((*info).si_pid, SIGUSR2);
			write(1, "\n", 1);
			return ;
		}
		g_mes.bit_position = 0;
		++(g_mes.str_position);
		if (g_mes.str_position == BUFFER)
			ft_message_printer();
	}
	usleep(USLEEP);
	kill((*info).si_pid, SIGUSR1);
}

static void	ft_receiver(void)
{
	struct sigaction	handler;

	handler.sa_sigaction = ft_bit_receiver;
	handler.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &handler, NULL);
	sigaction(SIGUSR2, &handler, NULL);
	while (g_mes.is_sending)
		pause();
}

int	main(void)
{
	char	message[BUFFER];

	g_mes.str = message;
	write(1, "PID: ", 5);
	ft_putnbr_fd(getpid(), 1);
	write(1, "\n", 1);
	while (1)
	{
		ft_init_message(&g_mes);
		ft_receiver();
	}
	return (0);
}

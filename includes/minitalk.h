/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spzona <spzona@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 14:43:10 by spzona            #+#    #+#             */
/*   Updated: 2022/02/03 13:25:01 by spzona           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <stdlib.h>
# include <unistd.h>
# define BUFFER 1024
# define USLEEP 40

typedef struct message
{
	char	*str;
	int		str_position;
	int		bit_position;
	int		is_sending;
}				t_message;

void	ft_putnbr_fd(int n, int fd);
int		ft_atoi(const char *str);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpuwar <kpuwar@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 23:48:47 by kpuwar            #+#    #+#             */
/*   Updated: 2023/01/03 18:44:33 by kpuwar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

unsigned char	g_bits[8];

static void	bits2char(void)
{
	unsigned char	c;
	int				multiplier;
	short			i;

	c = 0;
	multiplier = 1;
	i = 8;
	while (i--)
	{
		c += multiplier * (g_bits[i] - '0');
		multiplier *= 2;
	}
	ft_putchar(c);
}

static void	get_bits(int sig)
{
	static short	call;

	if (sig == SIGUSR1)
		g_bits[call % 8] = '0';
	else
		g_bits[call % 8] = '1';
	call++;
	if (call % 8 == 0 && call > 0)
		bits2char();
}

int	main(void)
{
	signal(SIGUSR1, get_bits);
	signal(SIGUSR2, get_bits);
	ft_printf("Server PID : [%i]\n", getpid());
	while (1)
		pause();
	exit(EXIT_SUCCESS);
}

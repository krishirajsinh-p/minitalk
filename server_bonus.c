/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpuwar <kpuwar@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 13:26:10 by kpuwar            #+#    #+#             */
/*   Updated: 2023/01/26 13:43:32 by kpuwar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

unsigned char	g_bits[8];

static char	bits2char(void)
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
	return (c);
}

static void	get_bits(int sig)
{
	static short	call;
	static char		cpid[5];
	char			c;

	if (sig == SIGUSR1)
		g_bits[call % 8] = '0';
	else
		g_bits[call % 8] = '1';
	call++;
	if (call % 8 == 0)
	{
		c = bits2char();
		if ((call / 8) <= 5)
			cpid[(call / 8) - 1] = c;
		if (c == '\0')
		{
			call = 0;
			kill(ft_atoi(cpid), SIGUSR1);
		}
		else
			ft_putchar(c);
	}
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

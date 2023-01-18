/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpuwar <kpuwar@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 13:26:07 by kpuwar            #+#    #+#             */
/*   Updated: 2023/01/18 13:41:30 by kpuwar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

unsigned char	g_bits[8];

static void	print_ack(int sig)
{
	if (sig == SIGUSR1)
	{
		ft_printf("This is an acknowledgement message,");
		ft_printf(" server has recieved the message!\n");
	}
}

static bool	error(int argc, int spid)
{
	if (argc != 3 || spid < 1)
	{
		ft_printf("client: illegal client command\n");
		ft_printf("usage:\t./client [<pid>] [<message>]\n");
		ft_printf("eg:\t./client 4242 \"hello world\"\n");
		return (true);
	}
	return (false);
}

static void	send_bits(pid_t pid)
{
	short	i;

	i = 0;
	while (i < 8)
	{
		if (g_bits[i++] == '0')
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(25);
	}
}

static void	str2bits(t_string s, pid_t pid)
{
	short			i;
	short			j;
	unsigned char	c;

	i = 0;
	while (s[i] != '\0')
	{
		c = s[i++];
		j = 8;
		while (j--)
		{
			g_bits[j] = (c % 2) + '0';
			c /= 2;
		}
		send_bits(pid);
	}
}

int	main(const int argc, const t_string argv[])
{
	pid_t		spid;
	t_string	msg;
	t_string	cpid;

	signal(SIGUSR1, print_ack);
	spid = ft_atoi(argv[1]);
	if (error(argc, spid) == true)
		exit(EXIT_FAILURE);
	msg = argv[2];
	cpid = ft_itoa(getpid());
	str2bits(cpid, spid);
	free(cpid);
	str2bits(": \t", spid);
	str2bits(msg, spid);
	str2bits("\n", spid);
	exit(EXIT_SUCCESS);
}

/*
send extra bit to state start of msg, end of pid & end of msg
*/
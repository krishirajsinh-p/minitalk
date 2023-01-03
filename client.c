/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpuwar <kpuwar@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 23:48:58 by kpuwar            #+#    #+#             */
/*   Updated: 2023/01/03 17:09:03 by kpuwar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

unsigned char	g_bits[8];

static void print_ack(int sig)
{
	if (sig == SIGUSR1)
		ft_printf("This is an acknowledgement message, server recieved the message!\n");
}

static t_bool	error(int argc, int spid)
{
	if (argc != 3 || spid < 1)
	{
		ft_printf("client: illegal client command\n");
		ft_printf("usage:\t./client [<pid>] [<message>]\n");
		ft_printf("eg:\t./client 4242 \"hello world\"\n");
		return (TRUE);
	}
	return (FALSE);
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

static void	char2bits(unsigned char c, pid_t pid)
{
	short	i;

	i = 8;
	while (i--)
	{
		g_bits[i] = (c % 2) + '0';
		c /= 2;
	}
	send_bits(pid);
}

int	main(const int argc, const t_string argv[])
{
	pid_t		spid;
	t_string	msg;
	t_string	cpid;
	short		i;

	signal(SIGUSR1, print_ack);
	spid = ft_atoi(argv[1]);
	if (error(argc, spid) == TRUE)
		exit(EXIT_FAILURE);
	msg = argv[2];
	cpid = ft_itoa(getpid());
	i = 0;
	while (cpid[i] != '\0')
		char2bits(cpid[i++], spid);
	free(cpid);
	char2bits(':', spid);
	char2bits('\t', spid);
	i = 0;
	while (msg[i] != '\0')
		char2bits(msg[i++], spid);
	char2bits('\n', spid);
	exit(EXIT_SUCCESS);
}

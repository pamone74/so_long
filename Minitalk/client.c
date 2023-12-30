/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamone <pamone@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 23:38:31 by pamone            #+#    #+#             */
/*   Updated: 2023/12/26 23:38:31 by pamone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minitalk.h"

volatile sig_atomic_t	g_receiver = 0;

void	ft_sig_handler(int signum, siginfo_t *info, void *context)
{
	static int	i;

	(void)context;
	(void)info;
	i = 0;
	g_receiver = 1;
	if (signum == SIGUSR2)
		i++;
	else if (signum == SIGUSR1)
	{
		ft_putstr_fd("The server have recived the message", 1);
		i = 0;
	}
}

int	ft_char_to_bin(char c, int pid)
{
	int	itr;
	int	bit_index;

	bit_index = 8;
	while (--bit_index >= 0)
	{
		itr = -1;
		if ((c >> bit_index) & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		while (g_receiver == 0)
		{
			if (++itr == 50)
			{
				write(1, "No Respond from this PID [", 27);
				ft_putnbr_fd(pid, 1);
				write(1, "]\n", 2);
				exit(1);
			}
			usleep(100);
		}
		g_receiver = 0;
	}
	return (0);
}

void	ft_input_handler(char **argv)
{
	struct sigaction	sa;
	int					server_pid;
	int					byte_index;

	server_pid = ft_atoi(argv[1]);
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = ft_sig_handler;
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		ft_putstr_fd("Eror sigaction", 1);
		exit(1);
	}
	byte_index = -1;
	while (argv[2][++byte_index])
		ft_char_to_bin(argv[2][byte_index], server_pid);
	ft_char_to_bin('\0', server_pid);
}

int	ft_is_valid(char *str)
{
	int	flag;

	flag = 1;
	while (*str)
	{
		if (!ft_isdigit(*str))
		{
			flag = 0;
			break ;
		}
		str ++;
	}
	return (flag);
}

int	main(int argc, char *argv[])
{
	if (argc != 3)
	{
		ft_putstr_fd("Usage : [Server_pid] [Messages]", 1);
		exit(1);
	}
	if (!ft_is_valid(argv[1]))
	{
		ft_putstr_fd("PID should be Digit", 1);
		exit(1);
	}
	ft_input_handler(argv);
	return (0);
}

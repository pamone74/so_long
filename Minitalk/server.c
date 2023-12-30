/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamone <pamone@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 23:49:10 by pamone            #+#    #+#             */
/*   Updated: 2023/12/26 23:49:10 by pamone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minitalk.h"

void	ft_bin_char(int signu, char *ch)
{
	if (signu == SIGUSR1)
		*ch = (*ch << 1) | 1;
	else if (signu == SIGUSR2)
		*ch <<= 1;
	else
		ft_putstr_fd("Invalid signal", 1);
}

void	ft_error(char *str)
{
	ft_putstr_fd(str, 1);
	exit(EXIT_FAILURE);
}

void	ft_sig_handler(int sig_num, siginfo_t *info, void *context)
{
	static int		i;
	static int		pid;
	static char		c;

	(void)context;
	pid = info->si_pid;
	ft_bin_char(sig_num, &c);
	if (++i == 8)
	{
		write(1, &c, 1);
		i = 0;
		if (!c)
		{
			kill(pid, SIGUSR1);
			write(1, "\n", 1);
			pid = 0;
			return ;
		}
		c = '\0';
	}
	kill(pid, SIGUSR2);
}

void	ft_print_pid(int nbr)
{
	write(1, "The server PID  [", 18);
	ft_putnbr_fd(nbr, 1);
	write(1, "]\n", 2);
}

int	main(void)
{
	volatile sig_atomic_t	byte_ready;
	struct sigaction		sa;

	ft_print_pid(getpid());
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = ft_sig_handler;
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		ft_error("Error sigaction");
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
		ft_error("Error sigaction");
	byte_ready = 0;
	while (1)
	{
		if (byte_ready)
			byte_ready = 0;
		pause();
	}
	return (0);
}

# include "ft_select.h"

int
	get_max_size_select(void)
{
	int	max;
	int	i;

	max = ft_strlen(g_mydata.strs[0]);
	i = -1;
	while (g_mydata.strs[++i] != NULL)
		if (ft_strlen(g_mydata.strs[i]) > max)
			max = ft_strlen(g_mydata.strs[i]);
	return (max);
}

void
	print_list_result(int fd)
{
	int	i;
	int	j;

	ft_putstr_fd(CL, 0);
	i = -1;
	j = 0;
	while (g_mydata.strs[++i] != NULL)
	{
		if (g_mydata.active[i] == 1)
		{
			if (j != 0)
				ft_putchar_fd(' ', fd);
			ft_putstr_fd(g_mydata.strs[i], fd);
			j++;
		}
	}
	if (j != 0)
		ft_putchar_fd('\n', fd);
}

void
	free_list_select(char **strs)
{
	int	i;

	i = -1;
	while (strs[++i] != NULL)
		free(strs[i]);
	if (strs != NULL)
		free(strs);
}

int
	get_strs_len(char **strs)
{
	int	i;

	i = -1;
	while (strs[++i] != NULL)
		;
	return (i);
}

void
	muve_curr(int dx, t_point2 size_ter, int max_size)
{
	int	size;
	int	cur_line;

	size = get_strs_len(g_mydata.strs);
	g_mydata.curr += dx;
	if (g_mydata.curr < 0)
		g_mydata.curr += size;
	g_mydata.curr %= size;
	cur_line = g_mydata.curr / (int)size_ter.x;
	while (cur_line > (g_mydata.curr_line + size_ter.y / max_size - 1))
		g_mydata.curr_line++;
	if (cur_line < g_mydata.curr_line)
		g_mydata.curr_line = cur_line;
}

void
	free_args(void)
{
	free_list_select(g_mydata.strs);
	free(g_mydata.type);
}

void	reset_default_conf(void)
{
	tcsetattr(STDERR_FILENO, TCSANOW, &g_mydata.old_settings);
}

void
	stop_signal()
{
	reset_default_conf();
	free_args();
	exit(1);
}

void
	sig_handler(int signo)
{
	if (signo == SIGTSTP)
		reset_default_conf();
	else if (signo == SIGINT || signo == SIGABRT || signo == SIGSTOP
			|| signo == SIGKILL || signo == SIGQUIT)
		stop_signal();
	else if (signo == SIGCONT)
	{
		set_keypress();
		init_signals();
		print_list_select();
	}
	else if (signo == SIGWINCH)
		print_list_select();
}

void
	init_signals()
{
	signal(SIGSTOP, sig_handler);
	signal(SIGINT, sig_handler);
	signal(SIGWINCH, sig_handler);
	signal(SIGABRT, sig_handler);
	signal(SIGCONT, sig_handler);
	signal(SIGKILL, sig_handler);
	signal(SIGQUIT, sig_handler);
}

void
	set_select(void)
{
	g_mydata.active[g_mydata.curr] = !g_mydata.active[g_mydata.curr];
}

int
	select_char(char c)
{
	int	i;

	i = g_mydata.curr;
	while (g_mydata.strs[++i] != NULL)
		if (g_mydata.strs[i][0] == c)
		{
			g_mydata.curr = i;
			return (1);
		}
	i = -1;
	while (++i < g_mydata.curr)
		if (g_mydata.strs[i][0] == c)
		{
			g_mydata.curr = i;
			return (1);
		}
	return (0);
}

void
	select_all(void)
{
	int		b;
	int		i;

	i = -1;
	b = 0;
	while (g_mydata.strs[++i] != NULL)
		if (g_mydata.active[i] == 0)
			b = 1;
	i = -1;
	while (g_mydata.strs[++i] != NULL)
		g_mydata.active[i] = b;
}

int
	main(int argc, char **argv)
{
	char		c[8];
	int			ret;

	if (argc <= 1)
		return (0);
	init_signals();
	init_mydata(argc, argv);
	set_keypress();
	print_list_select();
	while(get_strs_len(g_mydata.strs) != 0)
	{
		ret = read(STDERR_FILENO, &c, 8);
		if (ret == 1)
		{
			if (c[0] == ESC_KEY)
				break ;
			else if (c[0] == SPC_KEY || c[0] == ENTER_KEY)
			{
				set_select();
				muve_curr(1, ft_get_size_win_console(), get_max_size_select());
			}
			else if (c[0] == BSP_KEY)
			{
				if (ft_delete_strs() == 1)
					break ;
			}
			else if ((c[0] >= 'A' && c[0] <= 'Z') ||
						(c[0] >= 'a' && c[0] <= 'z') ||
						(c[0] >= '0' && c[0] <= '9'))
			{
				if (select_char(c[0]) == 0)
					continue ;
			}
			else if (c[0] == STAR_KEY)
				select_all();
			else
				continue ;
		}
		else if (ret == 3 && c[0] == '\033')
		{
			if (c[2] == RIGHT_KEY || c[2] == DOWN_KEY)
				muve_curr(1, ft_get_size_win_console(), get_max_size_select());
			else if (c[2] == LEFT_KEY || c[2] == UP_KEY)
				muve_curr(-1, ft_get_size_win_console(), get_max_size_select());
			else
				continue ;
		}
		else
			continue ;
		print_list_select();
	}
	reset_default_conf();
	print_list_result(STDOUT_FILENO);
	free_args();
	return (0);
}

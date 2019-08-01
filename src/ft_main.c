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
	print_list_select(void)
{
	int			i;
	int			j;
	t_point2	size;
	int			max_size;

	ft_putstr_fd(CL, 0);
	size = ft_get_size_win_console();
	max_size = get_max_size_select();
	i = -1;
	while (g_mydata.strs[++i] != NULL)
	{
		if (g_mydata.curr == i)
			ft_putstr_fd(STYLE_UNDERSCOPE, 0);
		if (g_mydata.active[i] == 1)
			ft_putstr_fd(STYLE_BOLD, 0);
		ft_putstr_fd(g_mydata.strs[i], 0);
		ft_putstr_fd(C_RESET, 0);
		j = 0;
		while (j + ft_strlen(g_mydata.strs[i]) <= max_size)
		{
			ft_putchar_fd(' ', 0);
			j++;
		}
		if (((i + 1) % (int)(size.y / (max_size + 1))) == 0)
			ft_putchar_fd('\n', 0);
	}
}

void
	print_list_result(int fd)
{
	int	i;

	ft_putstr_fd(CL, 0);
	i = -1;
	while (g_mydata.strs[++i] != NULL)
	{
		if (g_mydata.active[i] == 1)
		{
			if (i != 0)
				ft_putchar_fd(' ', fd);
			ft_putstr_fd(g_mydata.strs[i], fd);
		}
	}
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

char
	**get_strs_argv(int argc, char **argv)
{
	int		i;
	int		j;
	char	**res;

	res = (char **)malloc(sizeof(char *) * (argc));
	i = 0;
	j = -1;
	while (++i < argc)
		if (ft_strlen(argv[i]) > 0)
			res[++j] = ft_strdup(argv[i]);
	res[++j] = NULL;
	return (res);
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

char
	*type_list_get(char **strs, int size)
{
	char	*res;

	res = ft_strnew(size);
	ft_bzero(res, size);
	return (res);
}

void
	init_mydata(int argc, char **argv)
{
	g_mydata.strs = get_strs_argv(argc, argv);
	g_mydata.size = get_strs_len(g_mydata.strs);
	g_mydata.type = type_list_get(g_mydata.strs, g_mydata.size);
	g_mydata.curr = 0;
	g_mydata.active = ft_strnew(g_mydata.size);
	ft_bzero(g_mydata.active, g_mydata.size);
}

void
	muve_curr(int dx)
{
	int	size;

	size = get_strs_len(g_mydata.strs);
	g_mydata.curr += dx;
	if (g_mydata.curr < 0)
		g_mydata.curr += size;
	g_mydata.curr %= size;
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
			else if (c[0] == ENTER_KEY)
				set_select();
		}
		else if (ret == 3 && c[0] == '\033')
		{
			if (c[2] == UP_KEY)
				ft_putstr_fd("UP_KEY\n", 0);
			else if (c[2] == DOWN_KEY)
				ft_putstr_fd("DOWN_KEY\n", 0);
			else if (c[2] == RIGHT_KEY)
				muve_curr(1);
			else if (c[2] == LEFT_KEY)
				muve_curr(-1);
		}
		if (ret != 0)
			print_list_select();
	}
	reset_default_conf();
	print_list_result(STDOUT_FILENO);
	free_args();
	return (0);
}

# include "ft_select.h"

int
	get_max_size_select(t_mydata *mydata)
{
	int	max;
	int	i;

	max = ft_strlen(mydata->strs[0]);
	i = -1;
	while (mydata->strs[++i] != NULL)
		if (ft_strlen(mydata->strs[i]) > max)
			max = ft_strlen(mydata->strs[i]);
	return (max);
}

void
	print_list_select(t_mydata *mydata, int fd)
{
	int			i;
	int			j;
	t_point2	size;
	int			max_size;

	ft_putstr_fd(CL, 0);
	size = ft_get_size_win_console();
	max_size = get_max_size_select(mydata);
	i = -1;
	while (mydata->strs[++i] != NULL)
	{
		if (mydata->curr == i)
			ft_putstr_fd(STYLE_UNDERSCOPE, 0);
		if (mydata->active[i] == 1)
			ft_putstr_fd(STYLE_BOLD, 0);
		ft_putstr_fd(mydata->strs[i], 0);
		ft_putstr_fd(C_RESET, 0);
		j = 0;
		while (j + ft_strlen(mydata->strs[i]) <= max_size)
		{
			ft_putchar_fd(' ', 0);
			j++;
		}
		if (((i + 1) % (int)(size.y / (max_size + 1))) == 0)
			ft_putchar_fd('\n', 0);
	}
}

void
	print_list_result(t_mydata *mydata, int fd)
{
	int	i;

	ft_putstr_fd(CL, 0);
	i = -1;
	while (mydata->strs[++i] != NULL)
	{
		if (mydata->active[i] == 1)
		{
			if (i != 0)
				ft_putchar_fd(' ', fd);
			ft_putstr_fd(mydata->strs[i], fd);
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

t_mydata
	*init_mydata(int argc, char **argv)
{
	t_mydata	*mydata;

	mydata = (t_mydata *)malloc(sizeof(t_mydata));
	mydata->strs = get_strs_argv(argc, argv);
	mydata->size = get_strs_len(mydata->strs);
	mydata->type = type_list_get(mydata->strs, mydata->size);
	mydata->curr = 0;
	mydata->active = ft_strnew(mydata->size);
	ft_bzero(mydata->active, mydata->size);
	return (mydata);
}

void
	muve_curr(t_mydata *mydata, int dx)
{
	int	size;

	size = get_strs_len(mydata->strs);
	mydata->curr += dx;
	if (mydata->curr < 0)
		mydata->curr += size;
	mydata->curr %= size;
}

void		sig_handler(int signo)
{
}

void
	set_select(t_mydata *mydata)
{
	mydata->active[mydata->curr] = !mydata->active[mydata->curr];
}

int
	main(int argc, char **argv)
{
	char		c[8];
	int			ret;
	t_mydata	*mydata;

	if (argc <= 1)
		return (0);
	// signal(SIGINT, sig_handler);
	// signal(SIGTSTP, sig_handler);
	tgetent(NULL, getenv("TERM"));
	mydata = init_mydata(argc, argv);
	set_keypress();
	print_list_select(mydata, 0);
	while(get_strs_len(mydata->strs) != 0)
	{
		ret = read(STDERR_FILENO, &c, 8);
		if (ret == 1)
		{
			if (c[0] == ESC_KEY)
				break ;
			else if (c[0] == ENTER_KEY)
				set_select(mydata);
		}
		else if (ret == 3 && c[0] == '\033')
		{
			if (c[2] == UP_KEY)
				ft_putstr_fd("UP_KEY\n", 0);
			else if (c[2] == DOWN_KEY)
				ft_putstr_fd("DOWN_KEY\n", 0);
			else if (c[2] == RIGHT_KEY)
				muve_curr(mydata, 1);
			else if (c[2] == LEFT_KEY)
				muve_curr(mydata, -1);
		}
		if (ret != 0)
			print_list_select(mydata, 0);
	}
	print_list_result(mydata, STDOUT_FILENO);
	free_list_select(mydata->strs);
	free(mydata->type);
	free(mydata);
	return (0);
}

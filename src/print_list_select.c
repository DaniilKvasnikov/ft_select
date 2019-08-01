# include "ft_select.h"

void
	main_print(int i, int max_size)
{
	int			j;

	if (g_mydata.curr == i)
		ft_putstr_fd(STYLE_UNDERSCOPE, 0);
	if (g_mydata.active[i] == 1)
		ft_putstr_fd(STYLE_REVERSE, 0);
	ft_putstr_fd(g_mydata.strs[i], 0);
	ft_putstr_fd(C_RESET, 0);
	j = -1;
	while ((j + ft_strlen(g_mydata.strs[i])) < max_size)
	{
		ft_putchar_fd(' ', 0);
		j++;
	}
}

int
	max_count_words(t_point2 size, int max_size)
{
	int		in_line;

	in_line = size.y / max_size;
	return (size.x * in_line);
}

void
	print_list_select_vertical(t_point2 size, int max_size)
{
	int			i;
	int			j;
	int			count;

	count = get_strs_len(g_mydata.strs);
	if (count > max_count_words(size, max_size + 1))
		return ;
	i = -1;
	while (g_mydata.strs[++i] != NULL && i < size.x)
	{
		if (i != 0)
			ft_putchar_fd('\n', 0);
		j = 0;
		while ((i + j * size.x) < count)
		{
			main_print(i + j * size.x, max_size);
			j++;
		}
	}
}

void
	print_list_select_horizontal(t_point2 size, int max_size)
{
	int			i;
	int			count;

	count = get_strs_len(g_mydata.strs);
	if (count > max_count_words(size, max_size + 1))
		return ;
	i = -1;
	while (g_mydata.strs[++i] != NULL)
	{
		main_print(i, max_size);
		if (g_mydata.strs[i + 1] != NULL && ((i + 1) % (int)(size.y / (max_size + 1))) == 0)
			ft_putchar_fd('\n', 0);
	}
}

void
	print_list_select(void)
{
	t_point2	size;
	int			max_size;

	ft_putstr_fd(CL, 0);
	size = ft_get_size_win_console();
	max_size = get_max_size_select();
	print_list_select_horizontal(size, max_size);
	// print_list_select_vertical(size, max_size);
}

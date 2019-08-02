# include "ft_select.h"

int
	get_type(char *path)
{
	t_stat buff;

	lstat(path, &buff);
	if (access(path, F_OK) != 0)
		return (0);
	if ((buff.st_mode & S_IFMT) == S_IFDIR)
		return (TYPE_DIR);
	if ((buff.st_mode & S_IFMT) == __S_IFLNK)
		return (TYPE_LNK);
	if (access(path, X_OK) == 0)
		return (TYPE_BIN);
	return (0);
}

char
	*type_list_get(char **strs, int size)
{
	char	*res;
	int		j;

	res = ft_strnew(size);
	ft_bzero(res, size);
	j = -1;
	while (g_mydata.strs[++j] != NULL)
		res[j] = get_type(g_mydata.strs[j]);
	return (res);
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

void
	init_mydata(int argc, char **argv)
{
	g_mydata.strs = get_strs_argv(argc, argv);
	g_mydata.size = get_strs_len(g_mydata.strs);
	g_mydata.curr = 0;
	g_mydata.active = ft_strnew(g_mydata.size);
	g_mydata.type = type_list_get(g_mydata.strs, g_mydata.size);
	g_mydata.curr_line = 0;
	ft_bzero(g_mydata.active, g_mydata.size);
}

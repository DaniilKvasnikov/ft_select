# include "ft_select.h"

void
	strs_cpy(int num)
{
	int		i;
	int		j;
	char	*str;

	i = -1;
	j = -1;
	while (g_mydata.strs[++i] != NULL)
	{
		str = g_mydata.strs[i];
		if (i >= num)
		{
			g_mydata.strs[i] = g_mydata.strs[i + 1];
			g_mydata.type[i] = g_mydata.type[i + 1];
			g_mydata.active[i] = g_mydata.active[i + 1];
		}
		if (i == num)
			free(str);
	}
}

int
	ft_delete_strs(void)
{
	char	**strs;
	int		size;

	size = get_strs_len(g_mydata.strs) + 1;
	strs_cpy(g_mydata.curr);
	if (g_mydata.curr == (size - 2))
		g_mydata.curr = 0;
	return (size - 1);
}

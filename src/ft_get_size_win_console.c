# include "ft_select.h"

t_point2
	ft_get_size_win_console()
{
	struct winsize	ws;

	ioctl(STDIN_FILENO, TIOCGWINSZ, &ws);
	return ((t_point2){ws.ws_row, ws.ws_col});
}

#ifndef FT_SELECT_H
# define FT_SELECT_H

# include "ft_printf.h"
# include "ft_color.h"
# include "ft_structs.h"

# include <term.h>
# include <sys/ioctl.h>

# define ENTER_KEY				'\n'
# define ESC_KEY				'\033'
# define LEFT_KEY				'D'
# define UP_KEY					'A'
# define RIGHT_KEY				'C'
# define DOWN_KEY				'B'

# define CL (tgetstr("cl", NULL))

typedef struct			s_mydata
{
	char				**strs;
	int					curr;
	char				*type;
	char				*active;
	int					size;
	struct termios		old_settings;
	struct termios		new_settings;
}						t_mydata;

t_mydata				g_mydata;

void					set_keypress(void);
t_point2				ft_get_size_win_console();
void					sig_handler(int signo);
void					init_signals();

#endif

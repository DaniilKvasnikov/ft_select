#ifndef FT_SELECT_H
# define FT_SELECT_H

# include "ft_printf.h"
# include "ft_color.h"
# include "ft_structs.h"

# include <sys/stat.h>
# include <sys/types.h>
# include <term.h>
# include <sys/ioctl.h>

# define ENTER_KEY				'\n'
# define ESC_KEY				'\033'
# define BSP_KEY				127
# define SPC_KEY				' '
# define LEFT_KEY				'D'
# define UP_KEY					'A'
# define RIGHT_KEY				'C'
# define DOWN_KEY				'B'
# define STAR_KEY				'*'

# define TYPE_DIR				1
# define TYPE_LNK				2
# define TYPE_BIN				3

# define TYPE_DIR_COLOR			C_GREEN
# define TYPE_LNK_COLOR			C_BLUE
# define TYPE_BIN_COLOR			C_YELLOW

# define CL (tgetstr("cl", NULL))

typedef struct stat		t_stat;

typedef struct			s_mydata
{
	char				**strs;
	int					curr;
	int					curr_line;
	char				*type;
	char				*active;
	int					size;
	struct termios		old_settings;
	struct termios		new_settings;
}						t_mydata;

t_mydata				g_mydata;

void					set_keypress(void);
void					sig_handler(int signo);
void					init_signals();

t_point2				ft_get_size_win_console();
int						get_max_size_select(void);
int						get_strs_len(char **strs);

void					print_list_select(void);

void					init_mydata(int argc, char **argv);

int						ft_delete_strs(void);

#endif

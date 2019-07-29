#ifndef FT_SELECT_H
# define FT_SELECT_H

# include <unistd.h>
# include "ft_printf.h"

#include <stdlib.h>
#include <stdio.h>

#include <termios.h>
#include <string.h>

# define C_COLOR				"\033[35m"
# define O_COLOR				"\033[36m"
# define H_COLOR				"\033[34m"
# define MAKEFILE_COLOR			"\033[33m"
# define DOT_COLOR				"\033[32m"
# define DEFAULT_COLOR			"\033[0m"
# define A_COLOR				"\033[31m"
# define REVERSE_VIDEO_COLOR	"\033[7m"
# define UNDERLINED				"\033[4m"

# define ENTER_KEY				'\n'
# define ESC_KEY				'\033'
# define SPC_KEY				' '
# define STAR_KEY				42
# define MINUS_KEY				45
# define O_KEY					111
# define B_KEY					98
# define BSP_KEY				127
# define LEFT_KEY				'D'
# define UP_KEY					'A'
# define RIGHT_KEY				'C'
# define DOWN_KEY				'B'
# define DEL_KEY				2117294875L

static struct termios stored_settings;

#endif

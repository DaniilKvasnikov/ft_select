# include "ft_select.h"

static struct termios stored_settings;

void set_keypress(void)
{
	struct termios new_settings;

	tcgetattr(0,&stored_settings);

	new_settings = stored_settings;

	new_settings.c_lflag &= ~(ICANON | ECHO);
	new_settings.c_cc[VTIME] = 0;
	new_settings.c_cc[VMIN] = 1;

	tcsetattr(0,TCSANOW,&new_settings);
	return;
}

void reset_keypress(void)
{
	tcsetattr(0,TCSANOW,&stored_settings);
	return;
}

void		print_value_fd(char *str, int fd)
{
	ft_putstr_fd(str, fd);
}

int
	ft_printnbr(int nbr)
{
	ft_printf("%d", nbr);
	return (nbr);
}
#include <stdio.h>
#include <stdlib.h>
#include <termcap.h>
# define CL (tgetstr("cl", NULL))

int main()
{
	char	c[8];
	int		ret;

	tgetent(NULL, getenv("TERM"));

	set_keypress();
	ft_putstr_fd(CL, 0);
	while(1)
	{
		ret = read(STDERR_FILENO, &c, 8);
		if (ret != 0)			
			ft_putstr_fd(CL, 0);
		if (ret == 1)
		{
			if (c[0] == ESC_KEY)
				return (0);
			else if (c[0] == ENTER_KEY)
				ft_putstr_fd("ENTER_KEY\n", 0);
			else if (c[0] == SPC_KEY)
				ft_putstr_fd("SPC_KEY\n", 0);
			else if (c[0] == BSP_KEY)
				ft_putstr_fd("BSP_KEY\n", 0);
		}
		else if (ret == 3 && c[0] == '\033')
		{
			if (c[2] == UP_KEY)
				ft_putstr_fd("UP_KEY\n", 0);
			else if (c[2] == DOWN_KEY)
				ft_putstr_fd("DOWN_KEY\n", 0);
			else if (c[2] == RIGHT_KEY)
				ft_putstr_fd("RIGHT_KEY\n", 0);
			else if (c[2] == LEFT_KEY)
				ft_putstr_fd("LEFT_KEY\n", 0);
		}
		else if (ret == 1)
		{
			if (ret == 1)
				return (0);
		}
	}
}

// int main(void)
// {
// 	char	c[8];
// 	int		ret;
// 	char buf[1024];
// 	char buf2[30];
// 	char *ap = buf2;
// 	char *clearstr, *gotostr, *standstr, *stendstr;

// 	tgetent(buf, getenv("TERM"));

// 	clearstr = tgetstr("cl", &ap);
// 	gotostr = tgetstr("cm", &ap);
// 	standstr = tgetstr("so", &ap);
// 	stendstr = tgetstr("se", &ap);

// 	fputs(clearstr, stdout);
// 	fputs(tgoto(gotostr, 20, 10), stdout);
// 	printf("Hello, ");
// 	fputs(standstr, stdout);
// 	printf("world");
// 	fputs(stendstr, stdout);
// 	putchar('!');

// 	// set_keypress();

// 	while(1)
// 	{	
// 		tputs(tgetstr("cl", NULL), STDERR_FILENO, ft_printnbr);
// 		// putchar здесь вызывается для того, чтобы проверить работоспособность
// 		ret = read(STDERR_FILENO, &c, 8);
// 		if (ret == 1)
// 		{
// 			if (c[0] == ESC_KEY)
// 				return (0);
// 			else if (c[0] == ENTER_KEY)
// 				ft_printf("ENTER_KEY\n");
// 			else if (c[0] == SPC_KEY)
// 				ft_printf("SPC_KEY\n");
// 			else if (c[0] == BSP_KEY)
// 				ft_printf("BSP_KEY\n");
// 		}
// 		else if (ret == 3 && c[0] == '\033')
// 		{
// 			if (c[2] == UP_KEY)
// 				ft_printf("UP_KEY\n");
// 			else if (c[2] == DOWN_KEY)
// 				ft_printf("DOWN_KEY\n");
// 			else if (c[2] == RIGHT_KEY)
// 				ft_printf("RIGHT_KEY\n");
// 			else if (c[2] == LEFT_KEY)
// 				ft_printf("LEFT_KEY\n");
// 		}
// 		else if (ret == 1)
// 		{
// 			if (ret == 1)
// 				return (0);
// 		}
// 		ft_printf("len = %d\n", ret);
// 	}
// 	return 0;
// }
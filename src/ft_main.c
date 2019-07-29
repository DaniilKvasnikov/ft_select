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


int main(void)
{
	char	c[2];
	int		ret;
	set_keypress();

	print_value_fd("Hello\n", STDERR_FILENO);
	while(1)
	{	
		// putchar здесь вызывается для того, чтобы проверить работоспособность
		ret = read(STDERR_FILENO, &c, 2);
		if (c[0] == '\033')
		{
			if (ret == 1)
				return (0);
			else if (c[1] == 'A')
				ft_printf("%c\n", c[1]);
			else if (c[1] == 'B')
				ft_printf("%c\n", c[1]);
			else if (c[1] == 'C')
				ft_printf("%c\n", c[1]);
			else if (c[1] == 'D')
				ft_printf("%c\n", c[1]);
		}
		ft_printf("len =%d\n", ret);
		printf("%c\n", c[0]);
	}
	return 0;
}
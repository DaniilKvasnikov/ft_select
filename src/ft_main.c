# include "ft_select.h"

static struct termios stored_settings;

void set_keypress(void)
{
	struct termios new_settings;

	tcgetattr(0,&stored_settings);

	new_settings = stored_settings;

	new_settings.c_lflag &= (~ICANON & ~ECHO);
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

int main(void)
{
	char c;
	set_keypress();
	
	printf("Test: ");
	while(1)
	{	
		// putchar здесь вызывается для того, чтобы проверить работоспособность
		putchar(getchar());
	}
	return 0;
}
# include "ft_select.h"

void set_keypress(void)
{
	tgetent(NULL, getenv("TERM"));
	tcgetattr(0,&g_mydata.old_settings);

	g_mydata.new_settings = g_mydata.old_settings;

	g_mydata.new_settings.c_lflag &= ~(ICANON | ECHO);
	g_mydata.new_settings.c_cc[VTIME] = 0;
	g_mydata.new_settings.c_cc[VMIN] = 1;

	tcsetattr(0,TCSANOW,&g_mydata.new_settings);
	return;
}

void reset_keypress(void)
{
	tcsetattr(0,TCSANOW,&g_mydata.old_settings);
	return;
}

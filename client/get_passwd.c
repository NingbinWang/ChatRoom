#include<stdio.h>
#include<termios.h>
#include<unistd.h>
#include<assert.h>
#include<string.h>
#include <stdlib.h>
int getch()
{
	int c=0;
	struct termios org_opts, new_opts;
	int res=0;
	//-----  store old settings -----------
	res=tcgetattr(STDIN_FILENO, &org_opts);
	assert(res==0);
	//---- set new terminal parms --------
	memcpy(&new_opts, &org_opts, sizeof(new_opts));
	new_opts.c_lflag &= ~(ICANON | ECHO | ECHOE | ECHOK | ECHONL | ECHOPRT | ECHOKE | ICRNL);
	tcsetattr(STDIN_FILENO, TCSANOW, &new_opts);
	c=getchar();
	//------  restore old settings ---------
	res=tcsetattr(STDIN_FILENO, TCSANOW, &org_opts);
	assert(res==0);
	return c;
}

char * get_passwd()
{
    int i;
    char *pd = (char *)malloc(sizeof(char) * 128);

    for(i = 0; ; i++)
    {
	pd[i] = getch();

	if(pd[i] == '\n')
	{
	    pd[i] = '\0';

	    break;
	}

	if(pd[i] == 127)
	{
	    printf("\b \b");

	    i = i - 2;
	}
	else
	{
	    printf("*");
	}
	if(i<0)
	{
	    pd[0]='\0';
	}
    }
    return pd;
}

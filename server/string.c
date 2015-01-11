#include"data.h"
int my_strlen(const char *str)
{
	int len;
	while(*str++ != '\0')
	{
		len++;
	}
	return len;
}
int my_strcmp(const char *str1,const char *str2)
{
	if(str1 != NULL && str2 != NULL)
	{
	}
	else
	{
		return -2;
	}

	int i;
	while((*str1)!='\0' && (*str2) != '\0')
	{
		if((*str1) == (*str2))
		{
			str1++;
			str2++;
		}
		else
		{
			break;
		}
	}
	if((*str1) == '\0' && (*str2) == '\0')
	{
		return 0;
	}
	else
	{
		return (*str1) > (*str2)? 1 : -1;
	}
}
char  *my_strcpy( char *dest,const char *src)
{
	if(dest != NULL && src != NULL)
	{
	}
	else
	{
		return NULL;
	}
	char *adress = dest;
	while(((*dest++) = (*src++)) != '\0');
	return adress;
}
int my_atoi(const char *str)
{
	if(str != NULL)
	{
	}
	else
	{
		return -1;
	}
	const char* p = str;
	int minus = 0;
	long result = 0;
	if(*p == '-')
	{
		minus = 1;
		p++;
	}
	else if(*p == '+')
	{
		p++;
	}
	while(*p != '\0')
	{
		if(*p < '0' || *p >'9')
		{
			return -1;
		}
		result = result*10 + ((*p) - '0');
		p++;
	}
	minus = 1 ? -result:result;
	return result;
}

char * my_strcat(char *dest,const char *src)
{
	if(dest != NULL && src != NULL)
	{
	}
	else
	{
		return NULL;
	}
	char *address = dest;
	while((*dest) != '\0')
	{
		dest++;
	}
	while(((*dest++) = (*src++)) != '\0');
	return address;
}

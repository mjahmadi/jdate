#ifndef _HELPER_H
#define _HELPER_H

#include <sys/stat.h>
#include <sys/types.h>


int _div (int a, int b)
{
	return ((int)(a / b));
}


char *_substring (char s[], int p, int l)
{
   int c = 0;
   char *sub =  malloc(strlen(s) + 1);
 
   while (c < l) {
      sub[c++] = s[p + c - 1];
   }
   
   sub[c] = '\0';
   
   return sub;
}


char *_strconcat (const char *s1, const char *s2)
{
	char *result = malloc(strlen(s1) + strlen(s2) + 1);
	
	strcpy(result, s1);
	strcat(result, s2);
	
	return result;
}


char *_inttostr (int a) {
	char *str = malloc(sizeof(char*));
	sprintf(str, "%d", a);
	
	return str;
}


char *_append (const char *s, char c) {
    int len = strlen(s);
    char buf[len+2];
    
    strcpy(buf, s);
    buf[len] = c;
    buf[len + 1] = 0;
    
    return strdup(buf);
}


#endif //_HELPER_H


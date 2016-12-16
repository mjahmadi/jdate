#ifndef _HELPER_H
#define _HELPER_H

#define boolean unsigned short int
#define true    1
#define false   0

int _div (int a, int b)
{
	return ((int)(a / b));
}


char *_inttostr (int a) {
	char *str = malloc(sizeof(char)*20);
	sprintf(str, "%d", a);
	
	return str;
}


char *_strconcat (char *s1, const char *s2)
{
	char *result = malloc(sizeof(s1) + sizeof(s2) + 1);
	
	strcpy(result, s1);
	strcat(s1, s2);
	
	return s1;
}


char *_append (const char *s, char c) {
    int len = strlen(s);
    char buf[len+2];
    
    strcpy(buf, s);
    buf[len] = c;
    buf[len + 1] = 0;
    
    return strdup(buf);
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


#endif //_HELPER_H


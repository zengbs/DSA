#include<stdlib.h>
#include<string.h>
#include<stdio.h>


int main()
{
char str[] = "5234(+564))56464+546-364*5645646";
//printf("%f\n", (float)(str[0]-'0'));
//printf("%f\n", (float)('0'));
//printf("%f\n", (float)(str[0]));
//
//int i = 0;
//while(i<strlen(str)){
//  printf("%c", str[i]);
//  i++;
//}
//printf("\n");
//printf("%f\n", strtod(str, NULL));

char *pch;
pch = strtok (str,"+-*/()");

while (pch != NULL)
{
  printf ("%s\n",pch);
  pch = strtok (NULL, "+-*/()");
}


return 0;
}

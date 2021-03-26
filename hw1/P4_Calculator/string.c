#include<stdlib.h>
#include<string.h>
#include<stdio.h>


int main()
{
char *str = "5weffrewf\0ddd";
//printf("%f\n", (float)(str[0]-'0'));
//printf("%f\n", (float)('0'));
//printf("%f\n", (float)(str[0]));

int i = 0;
while(i<strlen(str)){
printf("%c", str[i]);

i++;
}
printf("\n");
return 0;
}

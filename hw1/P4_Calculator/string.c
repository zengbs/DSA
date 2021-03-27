#include<stdlib.h>
#include<string.h>
#include<stdio.h>

typedef unsigned char *byte_pointer;
void show_bytes(byte_pointer start, size_t len);

int main()
{
char str[] = " ";
//printf("%f\n", (float)(str[0]-'0')); //5
//printf("%f\n", (float)('0'));   // 48
//printf("%f\n", (float)(str[0])); //53
show_bytes((byte_pointer)str, 1);

//int i = 0;
//while(i<strlen(str)){
//  printf("%c", str[i]);
//  i++;
//}
//printf("\n");
//printf("%f\n", strtod(str, NULL));

//char *pch;
//pch = strtok (str,"+-*/()");
//
//while (pch != NULL)
//{
//  printf ("%s\n",pch);
//  pch = strtok (NULL, "+-*/()");
//}


return 0;
}

void show_bytes(byte_pointer start, size_t len) {
int i;
for (i = 0; i < len; i++)
printf(" %.2x", start[i]);
printf("\n");
}

#include<stdlib.h>
#include<string.h>
#include<stdio.h>

typedef unsigned char *byte_pointer;
void show_bytes(byte_pointer start, size_t len);

int main()
{
char str[] = {'0','1','\0','3','4','\0'};
//printf("%f\n", (float)(str[0]-'0')); //5
//printf("%c\n", '0');   // 48
//printf("%c\n", "0"[0]);   // 48
//printf("%c\n", '\0');   // 48
//printf("%f\n", (float)(str[0])); //53
//show_bytes((byte_pointer)str, 1);



for (int i=0;i<5;i++){
  printf("%c\n", str[i]);
}

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

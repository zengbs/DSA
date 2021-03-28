#include<limits.h>
#include<stdio.h>

int reverse(int x){
    int y=0;
    while(x!=0){
        if(y>INT_MAX/10||y<INT_MIN/10)return 0;
        else if(y==INT_MAX/10||y==INT_MIN/10){
            if(x%10>7||x%10<-8)return 0;
        }
        y=y*10+x%10;
        x/=10;
    }
    return y;
}

int main(){

int a = 123456;

printf("%d\n", reverse(a));

return 0;
}

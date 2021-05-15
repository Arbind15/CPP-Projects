#include <iostream>
#include <stdlib.h>
#include<conio.h>
#include<stdio.h>
#include<string.h>

using namespace std;

int poly(int a, int b)
{
    return (a+b);
}
float poly(float a, float b)
{
    return (a+b);
}
char * poly(char a[50],char b[50])
{
    int i=0;
    char c[100];
    for(i=0;i<strlen(a);i++)
    {
        c[i]=a[i];
    }

    for(i;i<strlen(a)+strlen(b);i++)
    {
        c[i]=b[i];
    }
    char *d=c;
     return d;
}

int main()
{
    printf("%d",poly(20,30.0));
    return 0;
}

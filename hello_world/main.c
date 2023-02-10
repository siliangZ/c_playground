#include <stdio.h>
int main()
{
    printf("hello world\n");
    printf("Please enter a interger\n");
    char str[100];
    int i;
    //%lf
    scanf("%s %d", str, &i);
    printf("You entered: %s, %d\n", str, i);
    return 0;
}
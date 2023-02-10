#include <iostream>

void int_to_binary(int value, char *result)
{
    size_t length = sizeof(result);
    for (size_t i = 0; i < length; i++)
    {
        if (value << i & 1)
        {
            //result[length - 1 - i] = '1';
            result[i] = '1';
        }
        else
        {
            //result[length - 1 - i] = '0';
            result[i] = '0';
        }
    }
}
int main()
{
    int v = 50;
    printf("the original value: %d.\n", v);
    char res[sizeof(v) * __CHAR_BIT__] = {0};
    int_to_binary(v, res);
    printf("converted binary: %s.\n", res);
}

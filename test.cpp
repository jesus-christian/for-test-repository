#include <stdio.h>
void smile()
{
    printf("Улыбайся!");
}
int main()
{
    for (int i = 3; i > 0; --i)
    {
        for (int j = i; j > 0; --j)
        {
            smile();
        }
        printf("\n");
    }
    return 0;
}

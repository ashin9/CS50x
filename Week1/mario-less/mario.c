#include <cs50.h>
#include <stdio.h>

// void print_char(int n);
void print_row(int spaces, int bricks);

int main(void)
{
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n <= 0);

    // slove 1 : 两层循环都在外面
    // print_char(n);

    // slove 2 : 主程序一层，外面抽象一层专门打印一行
    for (int i = 0; i < n; i++)
    {
        print_row((n - i - 1), (i + 1));
    }
}

// void print_char(int n)
// {
//     for (int i = 0; i < n; i++)
//     {
//         for (int j = 0; j < (n - i - 1); j++)
//         {
//             printf(" ");
//         }
//         for (int j = 0; j < i + 1; j++)
//         {
//             printf("#");
//         }
//         printf("\n");
//     }
// }

void print_row(int spaces, int bricks)
{
    for (int j = 0; j < spaces; j++)
    {
        printf(" ");
    }

    for (int j = 0; j < bricks; j++)
    {
        printf("#");
    }
    printf("\n");
}

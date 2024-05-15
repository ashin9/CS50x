#include <cs50.h>
#include <stdio.h>

int select_max(int remainder);

int main(void)
{
    // 接受非负输入：Change owed
    int owed;
    do
    {
        owed = get_int("Change owed: ");
    }
    while (owed < 0);

    // 贪心选择最大可支付硬币, n 为选择次数（也是硬币数量）
    int n = select_max(owed);
    printf("%d\n", n);
}

// 全局变量记录选择/递归次数
int recursion_count = 0;

int select_max(int remainder)
{

    // 递归边界
    if (remainder == 0)
    {
        return recursion_count;
    }

    // 递归体, 从大到小选择
    if (remainder >= 25)
    {
        remainder -= 25;
        recursion_count++;
        return select_max(remainder);
    }
    else if (remainder >= 10 && remainder < 25)
    {
        remainder -= 10;
        recursion_count++;
        return select_max(remainder);
    }
    else if (remainder >= 5 && remainder < 10)
    {
        remainder -= 5;
        recursion_count++;
        return select_max(remainder);
    }
    else
    {
        remainder -= 1;
        recursion_count++;
        return select_max(remainder);
    }
}

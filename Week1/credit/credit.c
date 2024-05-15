#include <cs50.h>
#include <stdio.h>

bool valid(long n);
void type(long n);
int get_len(long n);

int main(void)
{
    // 取 long 型 cardID 的输入
    long cardID;
    do
    {
        cardID = get_long("Number: ");
    }
    while (cardID < 1);

    // 判断 cardID 有效性
    if (valid(cardID))
    {
        // 判断 cardID 类型 : AMEX MASTERCARD VISA
        type(cardID);
    }
    else
    {
        printf("INVALID\n");
    }
}

bool valid(long n)
{
    int sum = 0;

    // 长度校验
    if (get_len(n) != 13 && get_len(n) != 15 && get_len(n) != 16)
        return false;

    // 1, 取倒数偶数位置的数字, 根据计算规则求和
    while (n > 0)
    {
        // 1.1 每次除 10 再模 10, 取到数字. 比如: 521, 除 10 为 52, 再模 10 为 2
        int second_to_last = (n / 10) % 10;
        // printf("second_to_last : %d\n", second_to_last);
        // 1.2 乘以 2
        second_to_last *= 2;
        // printf("second_to_last * 2 : %d\n", second_to_last);
        // 1.3 乘 2 后若为两位数, 则拆开相加, 否则直接相加
        if (get_len(second_to_last) == 2)
        {
            // 十位上的数字
            sum += (second_to_last / 10);
            // printf("second_to_last * 2 十位 : %d\n", (second_to_last / 10));
            // 个位上的数字
            sum += (second_to_last % 10);
            // printf("second_to_last * 2 个位 : %d\n", (second_to_last % 10));
        }
        else
        {
            sum += second_to_last;
        }

        // 2, 取倒数奇数位置的数字, 加和
        int first_to_last = n % 10;
        // printf("first_to_last : %d\n", first_to_last);
        sum += first_to_last;

        // printf("当前循环的 sum : %d\n", sum);

        // n 削去最右边（低位）两位
        n /= 100;
        // printf("%ld\n", n);
    }

    // 2, 取倒数奇数位置的数字, 加和
    // while (n >= 10)
    // {
    //     int first_to_last = n % 10;
    //     sum += first_to_last;

    //     // n 削去最右边（低位）两位
    //     n /= 100;
    //     printf("%ld\n", n);
    // }

    // printf("%d\n", sum);

    // 3, 判断尾数是否为 0
    if (sum % 10 == 0)
        return true;
    else
        return false;
}

int get_pre1(long n)
{
    while (n >= 10)
    {
        n /= 10;
    }
    return n;
}

int get_pre2(long n)
{
    while (n >= 100)
    {
        n /= 10;
    }
    return n;
}

int get_len(long n)
{
    // 10 以下 1 位，每除 10 一次，多一位
    int len = 1;
    while (n >= 10)
    {
        n /= 10;
        len++;
    }
    return len;
}

void identify_visa(long n)
{
    int pre1 = get_pre1(n);
    if (pre1 != 4)
        printf("INVALID\n");
    else
        printf("VISA\n");
}

void identify_amex(long n)
{
    int pre2 = get_pre2(n);
    if ((pre2 != 34) && (pre2 != 37))
        printf("INVALID\n");
    else
        printf("AMEX\n");
}

bool identify_mastercard(long n)
{
    int pre2 = get_pre2(n);
    if ((pre2 >= 51) && (pre2 <= 55))
    {
        printf("MASTERCARD\n");
        return true;
    }
    return false;
}

void type(long n)
{
    if (get_len(n) == 13)
        identify_visa(n);
    else if (get_len(n) == 15)
        identify_amex(n);
    else if (get_len(n) == 16)
    {
        if (identify_mastercard(n))
        {
        }
        else
        {
            identify_visa(n);
        }
    }
}

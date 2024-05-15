#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool only_digit(string argv);
string encrypt(string plaintext, int key);

int main(int argc, string argv[])
{
    // 接受参数, CLI 接受参数为字符, 需要转换为数字
    if (argc != 2 || !only_digit(argv[1]))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // 接受输入明文
    string plaintext = get_string("plaintext:  ");

    // 加密
    string chipher = encrypt(plaintext, atoi(argv[1]));

    // 打印输出密文
    printf("ciphertext: %s\n", chipher);

    return 0;
}

bool only_digit(string arg)
{
    for (int i = 0, len = strlen(arg); i < len; i++)
    {
        if (!isdigit(arg[i]))
        {
            return false;
        }
    }
    return true;
}

string encrypt(string plaintext, int key)
{
    string chipher = plaintext;

    for (int i = 0, len = strlen(plaintext); i < len; i++)
    {
        // 分小写, 大写, 字符
        if (islower(plaintext[i]))
        {
            chipher[i] = ((plaintext[i] - 97 + key) % 26) + 97;
        }
        else if (isupper(plaintext[i]))
        {
            chipher[i] = ((plaintext[i] - 65 + key) % 26) + 65;
        }
        else
        {
            chipher[i] = plaintext[i];
        }
    }
    return chipher;
}

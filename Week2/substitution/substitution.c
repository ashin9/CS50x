#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

bool checkkey(string arg);
string encrpt(string plaintext, string key);

int main(int argc, string argv[])
{
    // 检查参数
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    if (!checkkey(argv[1]))
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    // 接受明文
    string plaintext = get_string("plaintext:  ");

    // 加密
    string chipher = encrpt(plaintext, argv[1]);

    // 打印密文
    printf("ciphertext: %s\n", chipher);

    return 0;
}

bool checkkey(string arg)
{
    if (strlen(arg) != 26)
    {
        return false;
    }
    for (int i = 0, len = strlen(arg); i < len; i++)
    {
        // 检查 key 字符范围
        if (!((arg[i] >= 'a' && arg[i] <= 'z') || (arg[i] >= 'A' && arg[i] <= 'Z')))
            return false;
        // 检查 key 重复字符
        for (int j = i + 1; j < len; j++)
        {
            if (arg[i] == arg[j])
            {
                return false;
            }
        }
    }
    return true;
}

string encrpt(string plaintext, string key)
{
    string chipher = plaintext;

    for (int i = 0, len = strlen(plaintext); i < len; i++)
    {
        // 分大写, 小写, 字符 三种情况
        if (islower(plaintext[i]))
        {
            chipher[i] = tolower(key[plaintext[i] - 97]);
        }
        else if (isupper(plaintext[i]))
        {
            chipher[i] = toupper(key[plaintext[i] - 65]);
        }
        else
        {
            chipher[i] = plaintext[i];
        }
    }
    return chipher;
}

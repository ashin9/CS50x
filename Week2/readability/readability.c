#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

float compute_index(string text);

int compute_letters(string text);
int compute_words(string text);
int compute_sentence(string text);

float compute_l(int words, int letters);
float compute_s(int words, int sentences);

void print_grade(float index);

int main(void)
{
    // 输入
    string text = get_string("Text: ");

    // 衡量指标
    float index = compute_index(text);

    // 输出等级
    print_grade(index);
}

float compute_index(string text)
{
    // 根据空格, 把字符数组, 每 100 词分为一组, 100 words, 100 spaces
    // 遍历一遍记录索引, 相比每 100 词存为新字符串更快
    // int per_hundred_words_index[] =
    // int split_index = split_text(text);
    // 上面思路没必要,缺点是每 100words 的计算结果可能不同，还得取平均

    // 可以计算出总 words 数 / 100, 得出相对应 100 words 有多少 letters 和 sentens

    // 分别计算 letters, words, sentence
    int letters = compute_letters(text);
    int words = compute_words(text);
    int sentence = compute_sentence(text);

    // 计算 L
    float l = compute_l(words, letters);
    // 计算 S
    float s = compute_s(words, sentence);

    // 计算 index
    return (0.0588 * l - 0.296 * s - 15.8);
}

// int split_text(string text)
// {
//     // 记录每 100 words 的索引数组
//     int per_houndred_words_index[];
//     for (int i = 0, int count = 0, len = strlen(text); i < len; i++)
//     {
//         if (text[i] == ' ')
//         {
//             count++;
//         }
//         if ( count % 100 == 0)
//         {
//             per_houndred_words_index[] = i;
//         }
//     }
//     return
// }

int compute_letters(string text)
{
    int count = 0;
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (tolower(text[i]) >= 'a' && tolower(text[i]) <= 'z')
        {
            count++;
        }
    }
    return count;
}

int compute_words(string text)
{
    int count = 1;
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (text[i] == ' ')
        {
            count++;
        }
    }
    return count;
}

int compute_sentence(string text)
{
    int count = 0;
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            count++;
        }
    }
    return count;
}

float compute_l(int words, int letters)
{
    return letters / (words / 100.0);
}

float compute_s(int words, int sentences)
{
    return sentences / (words / 100.0);
}

void print_grade(float index)
{
    // 分三类, 两类特殊情况单独处理
    if (index <= 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", (int) round(index));
    }
}

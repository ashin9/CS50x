#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int compute_score(string s);
void print_result(int score1, int score2);

// 分数表
const int POINTS[] = {1, 3, 3, 2,  1, 4, 2, 4, 1, 8, 5, 1, 3,
                      1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int main(void)
{
    // 提示输入
    string s1 = get_string("Player1 : ");
    string s2 = get_string("Player2 : ");

    // 计算得分
    int score1 = compute_score(s1);
    int score2 = compute_score(s2);

    // 比较胜负
    print_result(score1, score2);
}

int compute_score(string s)
{
    int score = 0;
    // 遍历字符串, 挨个计算分数
    for (int i = 0, len = strlen(s); i < len; i++)
    {
        if (isupper(s[i]))
        {
            score += POINTS[s[i] - 'A'];
        }
        else
        {
            score += POINTS[s[i] - 'a'];
        }
    }
    return score;
}

void print_result(int score1, int score2)
{
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

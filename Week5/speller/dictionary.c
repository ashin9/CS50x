// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>

#include <string.h>     // strcpy
#include <strings.h>    // strcasecmp
#include <stdio.h>      // fopen fclose
#include <stdlib.h>     // malloc free

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// 字典大小
int dic_size = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int index = hash(word);
    // 遍历链表
    for (node *p = table[index]; p != NULL; p = p->next)
    {
        // 大小写不敏感检查
        if (strcasecmp(p->word, word) == 0)
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // 打开文件
    FILE *f = fopen(dictionary, "r");
    if (f == NULL)
    {
        return false;
    }

    // 读取每个 word
    char word[LENGTH + 1];  // 每行单词最长 45 字符 + \n
    while(fscanf(f, "%s", word) != EOF)
    {
        // 申请内存
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }

        // 结构体成员变量赋值, 字符串拷贝, 不能赋值
        strcpy(n->word, word);

        // 倒序头插法构建链表
        int index = hash(word);
        n->next = table[index];
        table[index] = n;

        // 记录字典 words 数
        dic_size++;
    }
    fclose(f);

    return true;
}
// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // 全局变量记录
    return dic_size;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    node *tmp = NULL;
    for (int i = 0; i < N; i++)
    {
        while(table[i] != NULL)
        {
            tmp = table[i];
            table[i] = table[i]->next;
            free(tmp);
        }
        if (i == N - 1 && table[i] == NULL)
        {
            return true;
        }
    }
    return false;
}

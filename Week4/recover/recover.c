#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // 参数处理
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    // 读取取证图像
    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        printf("%s cannot be opened for reading\n", argv[1]);
        return 1;
    }

    // 创建块缓冲区
    uint8_t buffer[512];

    // 匹配特征，并存储图像
    int cnt = 0;
    char filename[8];
    while (fread(buffer, 1, 512, card) == 512)
    {
        // 取字节前四位: & 0xf0
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // 格式化文件名
            sprintf(filename, "%03i.jpg", cnt);

            // 打开文件, 写入, 关闭
            FILE *jpg = fopen(filename, "a");
            fwrite(buffer, 1, 512, jpg);
            fclose(jpg);

            cnt++;
        }
        else
        {
            // 若第一次不是以特征开头呢？
            if (cnt == 0)
            {
                continue;
            }
            // 打开文件, 写入, 关闭, 追加写入
            FILE *jpg = fopen(filename, "a");
            fwrite(buffer, 1, 512, jpg);
            fclose(jpg);
        }
    }

    fclose(card);

}

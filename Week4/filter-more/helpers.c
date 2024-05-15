#include "helpers.h"

#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // 计算灰阶值并更新
            image[i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // 交换, 注意 -1
            tmp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = tmp;
        }
    }
    return;
}

RGBTRIPLE compute_blur(int h, int w, int height, int width, RGBTRIPLE image[height][width])
{
    float cnt = 0.0;
    double rgbRed = 0.0, rgbGreen = 0.0, rgbBlue = 0.0;

    for (int i = h - 1; i <= h + 1; i++)
    {
        for (int j = w - 1; j <= w + 1; j++)
        {
            // 过滤掉边缘
            if (i != -1 && j != -1 && i != height && j != width)
            {
                // 累加
                rgbRed += image[i][j].rgbtRed;
                rgbGreen += image[i][j].rgbtGreen;
                rgbBlue += image[i][j].rgbtBlue;
                // 计数
                cnt++;
            }
        }
    }

    RGBTRIPLE blured;
    // 计算均值并赋值
    blured.rgbtRed = round(rgbRed / cnt);
    blured.rgbtGreen = round(rgbGreen / cnt);
    blured.rgbtBlue = round(rgbBlue / cnt);

    return blured;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // 备份防止丢失数据
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // 遍历计算并更新
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = compute_blur(i, j, height, width, copy);
        }
    }
    return;
}

int min(int a, int b)
{
    return a < b ? a : b;
}

RGBTRIPLE compute_edges(int h, int w, int height, int width, RGBTRIPLE image[height][width])
{
    // 计算 box
    int Gxbox[3][3] = {{-1, 0, 1},
                       {-2, 0, 2},
                       {-1, 0, 1}};

    int Gybox[3][3] = {{-1, -2, -1},
                       {0, 0, 0},
                       {1, 2, 1}};

    double GxR = 0.0, GyR = 0.0, GxG = 0.0, GyG = 0.0, GxB = 0.0, GyB = 0.0;

    for (int i = h - 1; i <= h + 1; i++)
    {
        for (int j = w - 1; j <= w + 1; j++)
        {
            // 边缘当做纯黑 (0, 0, 0) 处理, 也就是: 不加即可
            if ( i != -1 && j != -1 && i != height && j != width)
            {
                GxR += Gxbox[i-(h-1)][j-(w-1)] * image[i][j].rgbtRed;
                GyR += Gybox[i-(h-1)][j-(w-1)] * image[i][j].rgbtRed;

                GxG += Gxbox[i-(h-1)][j-(w-1)] * image[i][j].rgbtGreen;
                GyG += Gybox[i-(h-1)][j-(w-1)] * image[i][j].rgbtGreen;

                GxB += Gxbox[i-(h-1)][j-(w-1)] * image[i][j].rgbtBlue;
                GyB += Gybox[i-(h-1)][j-(w-1)] * image[i][j].rgbtBlue;
            }
        }
    }

    RGBTRIPLE blured;
    blured.rgbtRed = min(round(sqrt(pow(GxR, 2) + pow(GyR, 2))), 255);
    blured.rgbtGreen = min(round(sqrt(pow(GxG, 2) + pow(GyG, 2))), 255);
    blured.rgbtBlue = min(round(sqrt(pow(GxB, 2) + pow(GyB, 2))), 255);

    return blured;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // 备份防止丢失数据
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // 遍历计算并更新
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = compute_edges(i, j, height, width, copy);
        }
    }
    return;
}

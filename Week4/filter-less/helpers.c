#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // 遍历所有像素
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // 取 RGB 均值作为灰度阶梯, 结构体指针, 访问用 ->
            RGBTRIPLE *rgb = &image[i][j];
            BYTE grayscale = round((rgb->rgbtRed + rgb->rgbtGreen + rgb->rgbtBlue) / 3.0);

            // 更新图像
            rgb->rgbtRed = grayscale;
            rgb->rgbtGreen = grayscale;
            rgb->rgbtBlue = grayscale;

            // int rgbt = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            // image[i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue = rgbt;
        }
    }

    return;
}

int min(int a, int b)
{
    return a < b ? a : b;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // 遍历所有像素
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // 取 RGB, 计算 sepia
            RGBTRIPLE *rgb = &image[i][j];
            BYTE sepiaRed = min(round(.393 * rgb->rgbtRed + .769 * rgb->rgbtGreen + .189 * rgb->rgbtBlue), 255);
            BYTE sepiaGreen = min(round(.349 * rgb->rgbtRed + .686 * rgb->rgbtGreen + .168 * rgb->rgbtBlue), 255);
            BYTE sepiaBlue = min(round(.272 * rgb->rgbtRed + .534 * rgb->rgbtGreen + .131 * rgb->rgbtBlue), 255);

            // 更新图像
            rgb->rgbtRed = sepiaRed;
            rgb->rgbtGreen = sepiaGreen;
            rgb->rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // 遍历每个像素
    for (int i = 0; i < height; i++)
    {
        // 遍历到一半即可, 丢失精度向下取整
        for (int j = 0; j < width / 2; j++)
        {
            // 交换, 数组传指针, 直接操作可影响函数外
            RGBTRIPLE rgb = image[i][j];
            image[i][j] = image[i][width - 1 - j];      // 注意是 width-1
            image[i][width - 1 - j] = rgb;
        }
    }
    return;
}

RGBTRIPLE compute_blur(int h, int w, int height, int width, RGBTRIPLE copy[height][width])
{
    float count = 0.0;
    double rgbRed = 0.0, rgbGreen = 0.0, rgbBlue = 0.0;

    // 遍历以当前元素为中心的方框
    for (int i = h - 1; i <= h + 1; i++)
    {
        for (int j = w - 1; j <= w + 1; j++)
        {
            // 过滤掉超出边缘的
            if ((i != -1) && (j != -1) && (i != height) && (j != width))
            {
                // ******** 调试了很久: 此处累加到 255 则溢出, 所以需要用更大类型存储
                rgbRed += copy[i][j].rgbtRed;
                rgbGreen += copy[i][j].rgbtGreen;
                rgbBlue += copy[i][j].rgbtBlue;
                count++;
            }
        }
    }
    // 平均
    RGBTRIPLE blur;
    blur.rgbtRed = round(rgbRed / count);
    blur.rgbtGreen = round(rgbGreen / count);
    blur.rgbtBlue = round(rgbBlue / count);

    return blur;
}
// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // 在原始数组中操作会影响其他像素的操作, 创建 copy 保留原始值
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // 遍历计算并更新 blur
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // RGBTRIPLE blur = compute_blur(i, j, height, width, copy);
            image[i][j] = compute_blur(i, j, height, width, copy);
        }
    }

    return;
}

#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int avg = round((image[i][j].rgbtRed + image[i][j].rgbtBlue + image[i][j].rgbtGreen) / 3.0);
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sepiaRed = round(0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue);
            int sepiaGreen = round(0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue);
            int sepiaBlue = round(0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue);

            if (sepiaRed > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed = sepiaRed;
            }

            if (sepiaGreen > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = sepiaGreen;
            }

            if (sepiaBlue > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = sepiaBlue;
            }
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {

            int tempRed = image[i][j].rgbtRed;
            int tempBlue = image[i][j].rgbtBlue;
            int tempGreen = image[i][j].rgbtGreen;

            image[i][j].rgbtRed = image[i][width - 1 - j].rgbtRed;
            image[i][j].rgbtGreen = image[i][width - 1 - j].rgbtGreen;
            image[i][j].rgbtBlue = image[i][width - 1 - j].rgbtBlue;

            image[i][width - 1 - j].rgbtRed = tempRed;
            image[i][width - 1 - j].rgbtGreen = tempGreen;
            image[i][width - 1 - j].rgbtBlue = tempBlue;
        }
    }
    return;
}



// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    
    RGBTRIPLE copy[height][width];
    
    int count = 0;
    float sumRed = 0;
    float sumBlue = 0;
    float sumGreen = 0;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
           
            if (i == 0)
            {
                if (j == 0)
                {
                    // target
                    sumRed += image[i][j].rgbtRed;
                    sumBlue += image[i][j].rgbtBlue;
                    sumGreen += image[i][j].rgbtGreen;

                    // target + 1
                    sumRed += image[i][j + 1].rgbtRed;
                    sumBlue += image[i][j + 1].rgbtBlue;
                    sumGreen += image[i][j + 1].rgbtGreen;
    
                    //height + 1
                    sumRed += image[i + 1][j].rgbtRed;
                    sumBlue += image[i + 1][j].rgbtBlue;
                    sumGreen += image[i + 1][j].rgbtGreen;

                    // height and width + 1
                    sumRed += image[i + 1][j + 1].rgbtRed;
                    sumBlue += image[i + 1][j + 1].rgbtBlue;
                    sumGreen += image[i + 1][j + 1].rgbtGreen;

                    count += 4;
                }
                else if (width - 1 == j)
                {
                    // target
                    sumRed += image[i][j].rgbtRed;
                    sumBlue += image[i][j].rgbtBlue;
                    sumGreen += image[i][j].rgbtGreen;

                    // target - 1
                    sumRed += image[i][j - 1].rgbtRed;
                    sumBlue += image[i][j - 1].rgbtBlue;
                    sumGreen += image[i][j - 1].rgbtGreen;

                    //height + 1
                    sumRed += image[i + 1][j].rgbtRed;
                    sumBlue += image[i + 1][j].rgbtBlue;
                    sumGreen += image[i + 1][j].rgbtGreen;

                    // height + and width - 1
                    sumRed += image[i + 1][j - 1].rgbtRed;
                    sumBlue += image[i + 1][j - 1].rgbtBlue;
                    sumGreen += image[i + 1][j - 1].rgbtGreen;

                    count += 4;
                }
                else
                {
                    // target
                    sumRed += image[i][j].rgbtRed;
                    sumBlue += image[i][j].rgbtBlue;
                    sumGreen += image[i][j].rgbtGreen;

                    // target - 1
                    sumRed += image[i][j - 1].rgbtRed;
                    sumBlue += image[i][j - 1].rgbtBlue;
                    sumGreen += image[i][j - 1].rgbtGreen;

                    // target + 1
                    sumRed += image[i][j + 1].rgbtRed;
                    sumBlue += image[i][j + 1].rgbtBlue;
                    sumGreen += image[i][j + 1].rgbtGreen;

                    //height + 1
                    sumRed += image[i + 1][j].rgbtRed;
                    sumBlue += image[i + 1][j].rgbtBlue;
                    sumGreen += image[i + 1][j].rgbtGreen;

                    // height + and width - 1
                    sumRed += image[i + 1][j - 1].rgbtRed;
                    sumBlue += image[i + 1][j - 1].rgbtBlue;
                    sumGreen += image[i + 1][j - 1].rgbtGreen;

                    // height and width + 1
                    sumRed += image[i + 1][j + 1].rgbtRed;
                    sumBlue += image[i + 1][j + 1].rgbtBlue;
                    sumGreen += image[i + 1][j + 1].rgbtGreen;

                    count += 6;
                }

            }   
            else if (height - 1 == i)
            {
                if (j == 0)
                {
                    // target
                    sumRed += image[i][j].rgbtRed;
                    sumBlue += image[i][j].rgbtBlue;
                    sumGreen += image[i][j].rgbtGreen;

                    // target + 1
                    sumRed += image[i][j + 1].rgbtRed;
                    sumBlue += image[i][j + 1].rgbtBlue;
                    sumGreen += image[i][j + 1].rgbtGreen;

                    //height - 1
                    sumRed += image[i - 1][j].rgbtRed;
                    sumBlue += image[i - 1][j].rgbtBlue;
                    sumGreen += image[i - 1][j].rgbtGreen;

                    // height -1 and width + 1
                    sumRed += image[i - 1][j + 1].rgbtRed;
                    sumBlue += image[i - 1][j + 1].rgbtBlue;
                    sumGreen += image[i - 1][j + 1].rgbtGreen;

                    count += 4;
                }
                else if (width - 1 == j)
                {
                    // target
                    sumRed += image[i][j].rgbtRed;
                    sumBlue += image[i][j].rgbtBlue;
                    sumGreen += image[i][j].rgbtGreen;

                    // target - 1
                    sumRed += image[i][j - 1].rgbtRed;
                    sumBlue += image[i][j - 1].rgbtBlue;
                    sumGreen += image[i][j - 1].rgbtGreen;

                    //height - 1
                    sumRed += image[i - 1][j].rgbtRed;
                    sumBlue += image[i - 1][j].rgbtBlue;
                    sumGreen += image[i - 1][j].rgbtGreen;

                    // height + and width - 1
                    sumRed += image[i - 1][j - 1].rgbtRed;
                    sumBlue += image[i - 1][j - 1].rgbtBlue;
                    sumGreen += image[i - 1][j - 1].rgbtGreen;

                    count += 4;
                }
                else
                {
                    // target
                    sumRed += image[i][j].rgbtRed;
                    sumBlue += image[i][j].rgbtBlue;
                    sumGreen += image[i][j].rgbtGreen;

                    // target - 1
                    sumRed += image[i][j - 1].rgbtRed;
                    sumBlue += image[i][j - 1].rgbtBlue;
                    sumGreen += image[i][j - 1].rgbtGreen;

                    // target + 1
                    sumRed += image[i][j + 1].rgbtRed;
                    sumBlue += image[i][j + 1].rgbtBlue;
                    sumGreen += image[i][j + 1].rgbtGreen;

                    //height - 1
                    sumRed += image[i - 1][j].rgbtRed;
                    sumBlue += image[i - 1][j].rgbtBlue;
                    sumGreen += image[i - 1][j].rgbtGreen;

                    // height - and width - 1
                    sumRed += image[i - 1][j - 1].rgbtRed;
                    sumBlue += image[i - 1][j - 1].rgbtBlue;
                    sumGreen += image[i - 1][j - 1].rgbtGreen;

                    // height - and width + 1
                    sumRed += image[i - 1][j + 1].rgbtRed;
                    sumBlue += image[i - 1][j + 1].rgbtBlue;
                    sumGreen += image[i - 1][j + 1].rgbtGreen;

                    count += 6;
                }
            }
            else if (j == 0)
            {
                // target
                sumRed += image[i][j].rgbtRed;
                sumBlue += image[i][j].rgbtBlue;
                sumGreen += image[i][j].rgbtGreen;

                // target + 1
                sumRed += image[i][j + 1].rgbtRed;
                sumBlue += image[i][j + 1].rgbtBlue;
                sumGreen += image[i][j + 1].rgbtGreen;

                //height - 1
                sumRed += image[i - 1][j].rgbtRed;
                sumBlue += image[i - 1][j].rgbtBlue;
                sumGreen += image[i - 1][j].rgbtGreen;

                // height -1 and width + 1
                sumRed += image[i - 1][j + 1].rgbtRed;
                sumBlue += image[i - 1][j + 1].rgbtBlue;
                sumGreen += image[i - 1][j + 1].rgbtGreen;

                //height + 1
                sumRed += image[i + 1][j].rgbtRed;
                sumBlue += image[i + 1][j].rgbtBlue;
                sumGreen += image[i + 1][j].rgbtGreen;

                //height + 1 and width +
                sumRed += image[i + 1][j + 1].rgbtRed;
                sumBlue += image[i + 1][j + 1].rgbtBlue;
                sumGreen += image[i + 1][j + 1].rgbtGreen;

                count += 6;
            }

            else if (width - 1 == j)
            {
                // target
                sumRed += image[i][j].rgbtRed;
                sumBlue += image[i][j].rgbtBlue;
                sumGreen += image[i][j].rgbtGreen;

                // target - 1
                sumRed += image[i][j - 1].rgbtRed;
                sumBlue += image[i][j - 1].rgbtBlue;
                sumGreen += image[i][j - 1].rgbtGreen;

                //height - 1
                sumRed += image[i - 1][j].rgbtRed;
                sumBlue += image[i - 1][j].rgbtBlue;
                sumGreen += image[i - 1][j].rgbtGreen;

                // height -1 and width - 1
                sumRed += image[i - 1][j - 1].rgbtRed;
                sumBlue += image[i - 1][j - 1].rgbtBlue;
                sumGreen += image[i - 1][j - 1].rgbtGreen;

                //height + 1
                sumRed += image[i + 1][j].rgbtRed;
                sumBlue += image[i + 1][j].rgbtBlue;
                sumGreen += image[i + 1][j].rgbtGreen;

                //height + 1 width -
                sumRed += image[i + 1][j - 1].rgbtRed;
                sumBlue += image[i + 1][j - 1].rgbtBlue;
                sumGreen += image[i + 1][j - 1].rgbtGreen;

                count += 6;
            }
            else
            {
                // target
                sumRed += image[i][j].rgbtRed;
                sumBlue += image[i][j].rgbtBlue;
                sumGreen += image[i][j].rgbtGreen;

                // target - 1
                sumRed += image[i][j - 1].rgbtRed;
                sumBlue += image[i][j - 1].rgbtBlue;
                sumGreen += image[i][j - 1].rgbtGreen;

                // target + 1
                sumRed += image[i][j + 1].rgbtRed;
                sumBlue += image[i][j + 1].rgbtBlue;
                sumGreen += image[i][j + 1].rgbtGreen;

                //height - 1
                sumRed += image[i - 1][j].rgbtRed;
                sumBlue += image[i - 1][j].rgbtBlue;
                sumGreen += image[i - 1][j].rgbtGreen;

                // height -1 and width - 1
                sumRed += image[i - 1][j - 1].rgbtRed;
                sumBlue += image[i - 1][j - 1].rgbtBlue;
                sumGreen += image[i - 1][j - 1].rgbtGreen;

                // height -1 and width + 1
                sumRed += image[i - 1][j + 1].rgbtRed;
                sumBlue += image[i - 1][j + 1].rgbtBlue;
                sumGreen += image[i - 1][j + 1].rgbtGreen;

                //height + 1
                sumRed += image[i + 1][j].rgbtRed;
                sumBlue += image[i + 1][j].rgbtBlue;
                sumGreen += image[i + 1][j].rgbtGreen;

                //height + 1 width -
                sumRed += image[i + 1][j - 1].rgbtRed;
                sumBlue += image[i + 1][j - 1].rgbtBlue;
                sumGreen += image[i + 1][j - 1].rgbtGreen;

                //height + 1 and width +
                sumRed += image[i + 1][j + 1].rgbtRed;
                sumBlue += image[i + 1][j + 1].rgbtBlue;
                sumGreen += image[i + 1][j + 1].rgbtGreen;

                count += 9;
            }

            copy[i][j].rgbtRed = round((float) sumRed / count);
            copy[i][j].rgbtGreen = round((float) sumGreen / count);
            copy[i][j].rgbtBlue = round((float) sumBlue / count);

            count = 0;
            sumRed = 0;
            sumBlue = 0;
            sumGreen = 0;

        }

    }
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = copy[i][j];
        }
        
    }       
    
}







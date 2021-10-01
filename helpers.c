#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    //Looping through the individual pixels in the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //Storing the current values in variables to average
            int tempBlue = image[i][j].rgbtBlue;
            int tempGreen = image[i][j].rgbtGreen;
            int tempRed = image[i][j].rgbtRed;

            //Getting the average of the three color values (from 0 to 255) to get a grey that is around the same brightness
            int grey = (tempBlue + tempGreen + tempRed) / 3;

            //Modifying the current image array and making it grey
            image[i][j].rgbtBlue = grey;
            image[i][j].rgbtGreen = grey;
            image[i][j].rgbtRed = grey;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    //Looping through the individual pixels in the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //Applying a Sepia algorithm on each of the individual RGB values
            int sepiaRed = round((.393 * image[i][j].rgbtRed) + (.769 * image[i][j].rgbtGreen) + (.189 * image[i][j].rgbtBlue));
            int sepiaGreen = round((.349 * image[i][j].rgbtRed) + (.686 * image[i][j].rgbtGreen) + (.168 * image[i][j].rgbtBlue));
            int sepiaBlue = round((.272 * image[i][j].rgbtRed) + (.534 * image[i][j].rgbtGreen) + (.131 * image[i][j].rgbtBlue));

            //Capping values using 8 bits
            if (sepiaRed > 255)
                sepiaRed = 255;
            if (sepiaGreen > 255)
                sepiaGreen = 255;
            if (sepiaBlue > 255)
                sepiaBlue = 255;


            //Assigning the new Sepia values to the original bitmap
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - j];
            image[i][width - j] = temp;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            int averageRed = 0;
            int averageGreen = 0;
            int averageBlue = 0;

            //Creating a counter for the average later
            int counter = 0;

            //Checking for the middle, seeing if the indexes are greater than 0 for bounds
            if (i >= 0 && j >= 0)
            {
                averageRed += image[i][j].rgbtRed;
                averageGreen += image[i][j].rgbtGreen;
                averageBlue += image[i][j].rgbtBlue;
                counter++;
            }

            //Checking for the top edge, seeing if our bounds are still valid after subtracting the height by 1
            if ((i - 1) >= 0 && j >= 0)
            {
                averageRed += image[i-1][j].rgbtRed;
                averageGreen += image[i-1][j].rgbtGreen;
                averageBlue += image[i-1][j].rgbtBlue;
                counter++;
            }

            //Checking for the bottom edge, seeing if our height is valid after increasing by 1
            if ((i + 1) < height && j >= 0)
            {
                averageRed += image[i+1][j].rgbtRed;
                averageGreen += image[i+1][j].rgbtGreen;
                averageBlue += image[i+1][j].rgbtBlue;
                counter++;
            }

            //Checking for the left edge, seeing if the j index is valid after subtracting by 1
            if ((j - 1) >= 0 && i >= 0)
            {
                averageRed += image[i][j-1].rgbtRed;
                averageGreen += image[i][j-1].rgbtGreen;
                averageBlue += image[i][j-1].rgbtBlue;
                counter++;
            }

            //Checking for the right edge, seeing if the j index is valid after adding 1
            if ((j + 1) < width && i >= 0)
            {
                averageRed += image[i][j+1].rgbtRed;
                averageGreen += image[i][j+1].rgbtGreen;
                averageBlue += image[i][j+1].rgbtBlue;
                counter++;
            }

            //Checking for the top left corner and its bounds
            if ((i - 1) >= 0 && (j - 1) >= 0)
            {
                averageRed += image[i-1][j-1].rgbtRed;
                averageGreen += image[i-1][j-1].rgbtGreen;
                averageBlue += image[i-1][j-1].rgbtBlue;
                counter++;
            }

            //Checking for the top right corner and its bounds
            if ((i - 1) >= 0 && (j + 1) < width)
            {
                averageRed += image[i-1][j+1].rgbtRed;
                averageGreen += image[i-1][j+1].rgbtGreen;
                averageBlue += image[i-1][j+1].rgbtBlue;
                counter++;
            }

            //Checking for the bottom left corner and its bounds
            if ((i + 1) < height && (j - 1) >= 0)
            {
                averageRed += image[i+1][j-1].rgbtRed;
                averageGreen += image[i+1][j-1].rgbtGreen;
                averageBlue += image[i+1][j-1].rgbtBlue;
                counter++;
            }

            //Checking for the bottom right corner and its bounds
            if ((i + 1) < height && (j + 1) < width)
            {
                averageRed += image[i+1][j+1].rgbtRed;
                averageGreen += image[i+1][j+1].rgbtGreen;
                averageBlue += image[i+1][j+1].rgbtBlue;
                counter++;
            }

            //Getting the average
            averageRed = averageRed / counter;
            averageGreen = averageGreen / counter;
            averageBlue = averageBlue / counter;

            image[i][j].rgbtRed = averageRed;
            image[i][j].rgbtGreen = averageGreen;
            image[i][j].rgbtBlue = averageBlue;
        }
    }
}

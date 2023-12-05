#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>
#include <stdbool.h>
#include <ctype.h>
#include <algorithm>
#include <list>
#include <string>
#include <iostream>

using namespace std;

static int my_size = 100;

int main(int argc, char *argv[])
{
    FILE *file;
    char file_name[32];
    int opt;
    char line[512];
    int rowlength;
    int rows = 0;
    int x;
    int y;
    int c_x;
    int c_y;
    int i;
    int x_left = 0;
    int x_right = 0;
    int y_up = 0;
    int y_down = 0;
    int matrix[my_size][my_size];
    int score[my_size][my_size];

    memset(score, 0, sizeof(score));

    strcpy(file_name, "puzzle-08-input.txt");

    while ((opt = getopt(argc, argv, "l:f:")) != -1) {
        switch (opt) {
            case 'f':
                strncpy(file_name, optarg, sizeof(file_name));
            break;
        }
    }

    if ((file = fopen(file_name, "r")) != NULL) {
        if (fgets(line, sizeof(line), file) != NULL) {
            rowlength = strnlen(line, sizeof(line)) - 1;
        }

        fclose(file);
    }

    if ((file = fopen(file_name, "r")) != NULL) {
        while (fgets(line, sizeof(line), file) != NULL) {
            for (i = 0; i < rowlength; i++) {
                matrix[i][rows] = line[i] - 48;
                score[i][rows] = 0;
            }
            rows++;
        }

        for (x = 1; x < rows - 1; x++) {
            for (y = 1; y < rowlength - 1; y++) {
                x_left = x_right = y_up = y_down = 0;

                for (c_x = x - 1; c_x >= 0; c_x--) {
                    x_left++;
                    if (matrix[c_x][y] >= matrix[x][y])
                        break;
                }

                for (c_x = x + 1; c_x < rows; c_x++) {
                    x_right++;
                    if (matrix[c_x][y] >= matrix[x][y])
                        break;
                }

                for (c_y = y - 1; c_y >= 0; c_y--) {
                    y_up++;
                    if (matrix[x][c_y] >= matrix[x][y])
                        break;
                }

                for (c_y = y + 1; c_y < rowlength; c_y++) {
                    y_down++;
                    if (matrix[x][c_y] >= matrix[x][y])
                        break;
                }

                score[x][y] = x_left * x_right * y_up * y_down;
            }
        }

        int max = 0;

        for (x = 0; x < rowlength; x++) {
            for (y = 0; y < rows; y++) {
                if (score[x][y] > max)
                    max = score[x][y];
            }
        }

        printf("Max score: %d\n", max);

        fclose(file);
    }
    else {
        printf("ERROR: Could not open file %s\n", file_name);
        return -1;
    }

    return 0;
}

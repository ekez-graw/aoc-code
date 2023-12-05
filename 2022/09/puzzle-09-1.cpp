#include <stdlib.h>
#include <stdio.h>
// #include <unistd.h>
#include <string.h>
// #include <getopt.h>
// #include <stdbool.h>
// #include <ctype.h>
// #include <algorithm>
// #include <list>
// #include <string>
// #include <iostream>

// using namespace std;

bool adjacent( int head_x, int head_y, int tail_x, int tail_y)
{
    if (head_x == tail_x && head_y == tail_y)
        return true;

    if (head_x == tail_x - 1 && head_y == tail_y)
        return true;

    if (head_x == tail_x - 1 && head_y == tail_y - 1)
        return true;

    if (head_x == tail_x && head_y == tail_y - 1)
        return true;

    if (head_x == tail_x + 1 && head_y == tail_y - 1)
        return true;

    if (head_x == tail_x + 1 && head_y == tail_y)
        return true;

    if (head_x == tail_x + 1 && head_y == tail_y + 1)
        return true;

    if (head_x == tail_x && head_y == tail_y + 1)
        return true;

    if (head_x == tail_x - 1 && head_y == tail_y + 1)
        return true;

    return false;
}

static int origo_x = 500;
static int origo_y = 500;

int main(int argc, char *argv[])
{
    FILE *file;
    char file_name[32];
    int opt;
    char line[512];
    int matrix[1000][1000];
    int x;
    int y;
    int head_x = origo_x;
    int head_y = origo_y;
    int tail_x = origo_x;
    int tail_y = origo_y;
    int head_x_new = origo_x;
    int head_y_new = origo_y;
    char dir;
    int steps;
    int max_head_x = origo_x;
    int min_head_x = origo_x;
    int max_head_y = origo_y;
    int min_head_y = origo_y;
    int row = 0;

    memset(matrix, 0, sizeof(matrix));

    strcpy(file_name, "puzzle-09-input.txt");

    printf("1 %d\n", adjacent(3,3,3,3));
    printf("2 %d\n", adjacent(3,3,2,3));
    printf("3 %d\n", adjacent(3,3,2,2));
    printf("4 %d\n", adjacent(3,3,3,2));
    printf("5 %d\n", adjacent(3,3,4,2));
    printf("6 %d\n", adjacent(3,3,4,3));
    printf("7 %d\n", adjacent(3,3,4,4));
    printf("8 %d\n", adjacent(3,3,3,4));
    printf("9 %d\n", adjacent(3,3,2,4));

    matrix[origo_x][origo_y] = 1;

    printf("Starting at: [%d:%d]\n", origo_x, origo_y);

    if ((file = fopen(file_name, "r")) != NULL) {
        while (fgets(line, sizeof(line), file) != NULL) {
            if (sscanf(line, "%c %d", &dir, &steps)) {
                row++;
                if (row == 1920)
                    printf("1920\n");
                while (steps > 0) {

                    if (dir == 'R') {
                        head_x_new++;
                    }

                    if (dir == 'L') {
                        head_x_new--;
                    }

                    if (dir == 'U') {
                        head_y_new++;
                    }

                    if (dir == 'D') {
                        head_y_new--;
                    }

                    if (adjacent( head_x_new, head_y_new, tail_x, tail_y) == false) {
                        tail_x = head_x;
                        tail_y = head_y;
                        matrix[tail_x][tail_y] = 1;
                    }

                    head_x = head_x_new;
                    head_y = head_y_new;

                    if (head_x > max_head_x)
                        max_head_x = head_x;
                    if (head_x < min_head_x)
                        min_head_x = head_x;
                    if (head_y > max_head_y)
                        max_head_y = head_y;
                    if (head_y < min_head_y)
                        min_head_y = head_y;

                    steps--;
                }
            }
        }

        int amount = 0;

        for (x = 0; x < 1000; x++) {
            for (y = 0; y < 1000; y++) {
                // printf("%d", matrix[x][y]);
                if (matrix[x][y] == 1) {
                    amount++;
                }
            }
            // printf("\n");
        }

        printf("Amount: %d\n", amount);

        printf("max_head_x: %d\n", max_head_x);
        printf("min_head_x: %d\n", min_head_x);
        printf("max_head_y: %d\n", max_head_y);
        printf("min_head_y: %d\n", min_head_y);

        fclose(file);
    }
    else {
        printf("ERROR: Could not open file %s\n", file_name);
        return -1;
    }

    return 0;
}

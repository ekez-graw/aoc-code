#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static int origo_x = 500;
static int origo_y = 500;
static int number_of_ropes = 10;

bool adjacent( int head_x, int head_y, int tail_x, int tail_y)
{
    if (head_x == tail_x && head_y == tail_y) return true;
    if (head_x == tail_x - 1 && head_y == tail_y) return true;
    if (head_x == tail_x - 1 && head_y == tail_y - 1) return true;
    if (head_x == tail_x && head_y == tail_y - 1) return true;
    if (head_x == tail_x + 1 && head_y == tail_y - 1) return true;
    if (head_x == tail_x + 1 && head_y == tail_y) return true;
    if (head_x == tail_x + 1 && head_y == tail_y + 1) return true;
    if (head_x == tail_x && head_y == tail_y + 1) return true;
    if (head_x == tail_x - 1 && head_y == tail_y + 1) return true;

    return false;
}

int main(int argc, char *argv[])
{
    FILE *file;
    char file_name[32];
    char line[32];
    char matrix[1000][1000];
    char p_matrix[1000][1000];
    int xx;
    int yy;
    int x[number_of_ropes];
    int y[number_of_ropes];
    int x_old = origo_x;
    int y_old = origo_y;
    int max_head_x = origo_x;
    int min_head_x = origo_x;
    int max_head_y = origo_y;
    int min_head_y = origo_y;
    int i;
    char dir;
    int steps;
    int row = 0;

    memset(matrix, 0, sizeof(matrix));
    memset(p_matrix, 0, sizeof(p_matrix));

    for (i = 0; i < number_of_ropes; i++) {
        x[i] = origo_x;
        y[i] = origo_y;
    }

    strcpy(file_name, "puzzle-09-input.txt");

    matrix[origo_x][origo_y] = 1;

    printf("Starting at: [%d:%d]\n", origo_x, origo_y);

    int x_temp;
    int y_temp;

    if ((file = fopen(file_name, "r")) != NULL) {
        while (fgets(line, sizeof(line), file) != NULL) {
            if (sscanf(line, "%c %d", &dir, &steps)) {
                row++;
                // printf("Row %d %c\n", row, dir);

                while (steps > 0) {
                    x_old = x[0];
                    y_old = y[0];
                    if (dir == 'R') x[0]++;
                    if (dir == 'L') x[0]--;
                    if (dir == 'U') y[0]++;
                    if (dir == 'D') y[0]--;

                    if (x[0] > max_head_x) max_head_x = x[0];
                    if (x[0] < min_head_x) min_head_x = x[0];
                    if (y[0] > max_head_y) max_head_y = y[0];
                    if (y[0] < min_head_y) min_head_y = y[0];

                    for (i = 0; i < (number_of_ropes - 1); i++) {
                        if (adjacent( x[i], y[i], x[i+1], y[i+1]) == false) {
                            if (y[i+1] == y[i] && x[i+1] < x[i]) { // Straight to the right
                                x[i+1]++;
                            } else
                            if (y[i+1] == y[i] && x[i+1] > x[i]) { // Straight to the left
                                x[i+1]--;
                            } else
                            if (x[i+1] == x[i] && y[i+1] < y[i]) { // Straight down
                                y[i+1]++;
                            } else
                            if (x[i+1] == x[i] && y[i+1] > y[i]) { // Straight up
                                y[i+1]--;
                            } else
                            if (x[i+1] > x[i] && y[i+1] > y[i]) {
                                x[i+1]--;
                                y[i+1]--;
                            } else
                            if (x[i+1] > x[i] && y[i+1] < y[i]) {
                                x[i+1]--;
                                y[i+1]++;
                            } else
                            if (x[i+1] < x[i] && y[i+1] > y[i]) {
                                x[i+1]++;
                                y[i+1]--;
                            } else
                            if (x[i+1] < x[i] && y[i+1] < y[i]) {
                                x[i+1]++;
                                y[i+1]++;
                            }
                        }
                        else {
                            break;
                        }
                        if (i == (number_of_ropes - 2))
                            matrix[ x[i+1] ][ y[i+1] ] = 1;
                    }

                    // memset(p_matrix, 0, sizeof(p_matrix));
                    // for (i = 9; i >= 1; i--)
                    //     p_matrix[ x[i] ][ y[i] ] = i + 48;
                    // p_matrix[ x[0] ][ y[0] ] = 72;

                    // printf("Step %d\n", steps);
                    // for (yy = 490; yy < 520; yy++) {
                    //     for (xx = 480; xx < 520; xx++) {
                    //         if (p_matrix[xx][yy] == 0)
                    //             printf("%c", '.');
                    //         else
                    //             printf("%c", p_matrix[xx][yy]);
                    //     }
                    //     printf("\n");
                    // }

                    // printf("\n");
                    steps--;
                }
            }
        }

        int amount = 0;

        for (xx = 0; xx < 1000; xx++) {
            for (yy = 0; yy < 1000; yy++) {
                // printf("%c", matrix[xx][yy] ? '#' : '.');
                if (matrix[xx][yy] == 1) {
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

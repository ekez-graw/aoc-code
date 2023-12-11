// (c) Leif Enblom
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

class Galaxy {
public:
    Galaxy(u_int32_t in_nr);
    void set_coords(u_int32_t in_y, u_int32_t in_x);

    u_int32_t y;
    u_int32_t x;

    u_int32_t nr;
};

Galaxy::Galaxy(u_int32_t in_nr) : y(0),
                                  x(0),
                                  nr(in_nr) {}

void Galaxy::set_coords(u_int32_t in_y, u_int32_t in_x)
{
    y = in_y;
    x = in_x;
}

Galaxy *uni[200][200];

int main(int argc, char *argv[])
{
    FILE *file;
    char file_name[64];
    char line[256];
    int x;
    int y;
    int xn;
    int yn;
    int x_max = 0;
    int y_max = 0;
    int x_tmp;
    int y_tmp;
    int nr_found;
    int distance;
    long int total_distance = 0;
    int nr_of_galaxies = 0;
    u_int32_t galaxy_nr = 0;
    u_int32_t galaxy_next_nr;
    size_t len;

    memset(uni, 0, sizeof(uni));
    strcpy(file_name, "/home/dad/src/aoc/aoc-data/2023/p11-input.txt");

    if ((file = fopen(file_name, "r")) != NULL) {
        while (fgets(line, sizeof(line), file) != NULL) {
            len = strlen(line);
            for (x = 0; x < len; x++) {
                if (line[x] == '#') {
                    uni[y_max][x] = new Galaxy(y_max);
                }
            }
            y_max++;
        }
        x_max = x;

        // Expand universe (y)
        for (y = 0; y < y_max; y++) {
            nr_found = 0;
            for (x = 0; x < x_max; x++)
                if (uni[y][x] != NULL)
                    nr_found++;
            if (nr_found == 0) {
                for (y_tmp = y_max - 1; y_tmp > y; y_tmp--) {
                    for (x = 0; x < x_max; x++) {
                        uni[y_tmp + 1][x] = uni[y_tmp][x];
                        uni[y_tmp][x] = NULL;
                    }
                }
                y++;
                y_max++;
            }
        }

        // Expand universe (x)
        for (x = 0; x < x_max; x++) {
            nr_found = 0;
            for (y = 0; y < y_max; y++)
                if (uni[y][x] != NULL)
                    nr_found++;
            if (nr_found == 0) {
                for (x_tmp = x_max - 1; x_tmp > x; x_tmp--) {
                    for (y = 0; y < y_max; y++) {
                        uni[y][x_tmp + 1] = uni[y][x_tmp];
                        uni[y][x_tmp] = NULL;
                    }
                }
                x++;
                x_max++;
            }
        }

        // Iterate over all galaxies and calculate distance to all consecutive ones.
        for (y = 0; y < y_max; y++) {
            for (x = 0; x < x_max; x++) {
                if (uni[y][x] != NULL) {
                    galaxy_nr++;
                    printf("Galaxy %3d\n", galaxy_nr);
                    galaxy_next_nr = 0;
                    for (yn = 0; yn < y_max; yn++) {
                        for (xn = 0; xn < x_max; xn++) {
                            if (uni[yn][xn] != NULL) {
                                galaxy_next_nr++;
                                if (galaxy_next_nr > galaxy_nr) {
                                    distance = abs(yn - y);
                                    distance += abs(xn - x);
                                    total_distance += distance;
                                    printf("  [%3d][%3d] --> [%3d][%3d] = %12d [Tot: %6ld]\n", y, x, yn, xn, distance, total_distance);
                                }                                
                            }
                        }
                    }
                }
            }
        }

        // Print universe
        for (y = 0; y < y_max; y++) {
            for (x = 0; x < x_max; x++) {
                if (uni[y][x] != NULL)
                    printf("#");
                else
                    printf(".");
            }
            printf("\n");
        }

        fclose(file);
    }

    printf("Total Lengths: %lu\n", total_distance);

    return 0;
}
